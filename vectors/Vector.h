#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <stdexcept>

using std::size_t;

template <class T>
class Vector {
    enum { CHUNK = 10 };
    size_t capacity;    // Size of the current array allocation (total number of ints, in use or not)
    size_t n_elems;     // Number of int spaces currently in use, starting from position 0
    T* data_ptr;      // Pointer to the heap array
    void grow();
public:
    // Object Mgt.
    Vector();
    Vector(const Vector<T> &v);            // Copy constructor
    Vector<T> &operator=(const Vector<T> &v); // Copy assignment operator
    ~Vector();
    // Accessors
    T front() const;                  // Return the int in position 0, if any
    T back() const;                   // Return last element (position n_elems-1)
    T at(size_t pos) const;           // Return element in position "pos" (0-based)
    size_t size() const;                // Return n_elems
    bool empty() const;                 // Return n_elems == 0
    // Mutators
    T& operator[](size_t pos);        // Same as at but no bounds checking
    void push_back(T item);           // Append a new element at the end of the array
    void pop_back();                    // --n_elems (nothing else to do; returns nothing)
    void erase(size_t pos);             // Remove item in position pos and shuffles following items left
    void insert(size_t pos, T item);  // Shuffle items right to make room for a new element
    void clear();                       // n_elems = 0 (nothing else to do; keep the current capacity)
    // Iterators
    T* begin();                       // Return a pointer to 1st element, or nullptr if n_elems == 0
    T* end();                         // Return a pointer to 1 past last element, or nullptr if n_elems == 0
    // Comparators
    bool operator==(const Vector<T> &v) const;
    bool operator!=(const Vector<T> &v) const;
};

template <class T>
void Vector<T>::grow() {
    T* temp = new T[int(1.6 * capacity)];
    for (int i = 0; i < capacity; i++) {
        temp[i] = data_ptr[i];
    }
    delete[] data_ptr;
    capacity *= 1.6;
    data_ptr = temp;
}

template <class T>
Vector<T>::Vector() {
    data_ptr = new T[CHUNK];
    capacity = CHUNK;
    n_elems = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& v) {
    capacity = v.capacity;
    data_ptr = new T[capacity];
    n_elems = v.n_elems;
    for (int i = 0; i < n_elems; i++) {
        data_ptr[i] = v.at(i);
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &v) {
    if (this != &v) {
        delete[] data_ptr;
        data_ptr = new T[capacity];
        capacity = v.capacity;
        n_elems = v.n_elems;
        for (int i = 0; i < v.size(); i++) {
            data_ptr[i] = v.at(i);
        }
    }
    return *this;
}

template <class T>
Vector<T>::~Vector() {
    delete[] data_ptr;
}

template <class T>
T Vector<T>::front() const {
    if (n_elems == 0) {
        throw std::range_error("Out of range");
    }
    else {
        return data_ptr[0];
    }
}

template <class T>
T Vector<T>::back() const {
    if (n_elems == 0) {
        throw std::range_error("Out of range");
    }
    else {
        return data_ptr[n_elems - 1];
    }
}

template <class T>
T Vector<T>::at(size_t pos) const {
    if (n_elems <= 0) {
        throw std::range_error("No elemnts (at)");
    }
    else if (pos > (n_elems - 1)) {
        throw std::range_error("OOR (at)");
    }
    else {
        return data_ptr[pos];
    }
}

template <class T>
size_t Vector<T>::size() const {
    return n_elems;
}

template <class T>
bool Vector<T>::empty() const {
    return n_elems == 0;
}

template <class T>
T& Vector<T>::operator[](size_t pos) {
    return data_ptr[pos];
}

template <class T>
void Vector<T>::push_back(T item) {
    if (n_elems == capacity) {
        grow();
    }
    data_ptr[n_elems] = item;
    n_elems++;
}

template <class T>
void Vector<T>::pop_back() {
    if (n_elems <= 0) {
        throw std::range_error("No elements (pop");
    }
    else {
        --n_elems;
    }
}

template <class T>
void Vector<T>::erase(size_t pos) {
    if (n_elems <= 0) {
        throw std::range_error("No elements (erase)");
    }
    else if (pos > (n_elems - 1)) {
        throw std::range_error("OOR (erase)");
    }
    else {
        for (int i = pos; i < n_elems; i++) {
            data_ptr[i] = data_ptr[i + 1];
        }
        --n_elems;
    }
}

template <class T>
void Vector<T>::insert(size_t pos, T item) {
    if (n_elems <= 0) {
        throw std::range_error("No elements(erase)");
    }
    else if (pos > (n_elems - 1)) {
        grow();
        for (int i = n_elems; i > pos; i--) {
            data_ptr[i] = data_ptr[i - 1];
        }
        data_ptr[pos] = item;
        ++n_elems;
    }
    else if (n_elems == capacity) {
        push_back(item);
    }
    else {
        for (int i = n_elems; i > pos; i--) {
            data_ptr[i] = data_ptr[i - 1];
        }
        data_ptr[pos] = item;
        ++n_elems;
    }
}

template <class T>
void Vector<T>::clear() {
    n_elems = 0; //might have to change haha
}

template <class T>
T* Vector<T>::begin() {
    if (n_elems == 0) {
        return nullptr;
    }
    else {
        return data_ptr;
    }
}

template <class T>
T* Vector<T>::end() {
    if (n_elems == 0) {
        return nullptr;
    }
    else {
        return data_ptr + n_elems;
    }
}

template <class T>
bool Vector<T>::operator==(const Vector<T> &v) const {
    if (n_elems == v.size()) {
        for (int i = 0; i < v.size() && i < n_elems; i++) {
            if (data_ptr[i] != v.at(i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <class T>
bool Vector<T>::operator!=(const Vector<T> &v) const {
    return !(*this == v);
}
#endif