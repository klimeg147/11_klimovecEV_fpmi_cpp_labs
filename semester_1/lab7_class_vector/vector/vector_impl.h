#pragma once
#include <initializer_list>
#include <iostream>
#include <cstdint>

class Vector {
private:
    size_t size_ = 0, capacity_ = 0;
    int* arr_ = nullptr;
        
public:
    Vector() : size_(0), capacity_(0), arr_(nullptr) {
        std::cout << "Default\n";
    }

    Vector(size_t amount) : size_(amount), capacity_(amount), arr_(new int[size_]) {
        std::cout << "User defined\n";
        for (size_t i = 0; i < amount; ++i) {
            arr_[i] = 0;
        }
    }

    Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()), arr_(new int[size_]) {

        size_t i = 0;
        for (int item : list) {
            arr_[i] = item;
            ++i;
        }
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), arr_(new int[size_]) {

        std::cout << "Copy ctor\n";
        std::copy(other.arr_, other.arr_ + size_, arr_);
    }

    ~Vector() {
        std::cout << "Destructor\n";
        delete[] arr_;
    }

    Vector& operator=(const Vector& other) {
        std::cout << "operator=\n";

        if (this == &other) {
            return *this;
        }
        Vector copy(other);
        Swap(copy);

        return *this;
    }

    void Swap(Vector& other) {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(arr_, other.arr_);
    }

    int& operator[](size_t index) {
        return arr_[index];
    }

    const int& operator[](size_t index) const {
        return arr_[index];
    }

    const int& At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("inputed index is out of range");
        }
        return arr_[index];    
    }

    int& At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("inputed index is out of range");
        }
        return arr_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int num) {
        if (size_ >= capacity_) {
            capacity_ = (capacity_ == 0 ? 1 : capacity_ * 2);
            int* arr_2 = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                arr_2[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = arr_2;
        }
        arr_[size_] = num;
        size_++;
    }


    void PopBack() {
        if (size_ > 0) {
            size_--;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t capacity) {
        std::cout << "reserve done\n";
        if (capacity > capacity_) {
            int* arr_2 = new int[capacity];
            for (size_t i = 0; i < size_; ++i) {
                arr_2[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = arr_2;
            capacity_ = capacity;
        }
    }
};

std::ostream& operator<<(std::ostream&, const Vector&);