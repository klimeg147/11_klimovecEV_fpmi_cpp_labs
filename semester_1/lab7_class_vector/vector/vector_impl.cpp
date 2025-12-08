#include "vector_impl.h"

std::ostream& operator<<(std::ostream& out, const Vector& vec) {

    out << "[";
    for (size_t i = 0; i < vec.Size(); ++i) {
        out << vec[i];
        if (i != vec.Size() - 1) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}