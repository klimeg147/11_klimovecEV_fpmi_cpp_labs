#include "forward_list_impl.h"
#include <iostream>


ForwardList::ForwardList() : head_(nullptr), size_(0) {
}


ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {

    if (rhs.head_ == nullptr) {
        return;
    }

    head_ = new Node(rhs.head_->value_);
    size_ = 1;

   
    Node* current_this = head_;
    Node* current_rhs = rhs.head_->next_;

    while (current_rhs != nullptr) {
        current_this->next_ = new Node(current_rhs->value_);
        current_this = current_this->next_;
        current_rhs = current_rhs->next_;
        ++size_;
    }
}


ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}


ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    for (auto it = init.end(); it != init.begin();) {
        --it;
        PushFront(*it);
    }
}


ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }

    Clear();

    if (rhs.head_ == nullptr) {
        return *this;
    }

    head_ = new Node(rhs.head_->value_);
    size_ = 1;

    Node* current_this = head_;
    Node* current_rhs = rhs.head_->next_;

    while (current_rhs != nullptr) {
        current_this->next_ = new Node(current_rhs->value_);
        current_this = current_this->next_;
        current_rhs = current_rhs->next_;
        ++size_;
    }

    return *this;
}


ForwardList::~ForwardList() {
    Clear();
}


void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    ++size_;
}


void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }

    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
    --size_;
}


void ForwardList::Remove(int32_t value) {

    while (head_ != nullptr && head_->value_ == value) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        --size_;
    }

    if (head_ == nullptr) {
        return;
    }

    Node* current = head_;
    while (current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* temp = current->next_;
            current->next_ = temp->next_;
            delete temp;
            --size_;
        } else {
            current = current->next_;
        }
    }
}


void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    size_ = 0;
}


bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}


void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            out << " ";
        }
        out << current->value_;
        first = false;
        current = current->next_;
    }
}


int32_t ForwardList::Front() const {
    return head_->value_;
}


size_t ForwardList::Size() const {
    return size_;
}