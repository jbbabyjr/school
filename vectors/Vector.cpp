//#include "Vector.h"
//#include <iostream>
//#include <stdexcept>
//
//using namespace std;
//
//void Vector::grow() {
//	//use copy assignment while making a new one.
//	cout << "grow" << endl;
//	int* temp = new int[int(1.6 * capacity)];
//	for (int i = 0; i < capacity; i++) {
//		temp[i] = data_ptr[i];
//	}
//	delete[] data_ptr;
//	capacity *= 1.6;
//	data_ptr = temp;
//}
//
//// Object Mgt.
//Vector::Vector() {
//	data_ptr = new int[CHUNK];
//	capacity = CHUNK;
//	n_elems = 0;
//}
//Vector::Vector(const Vector& v) {
//	data_ptr = new int[v.capacity];
//	capacity = v.capacity;
//	n_elems = v.n_elems;
//	for (int i = 0; i < v.size(); i++) {
//		data_ptr[i] = v.at(i);
//	}
//}        // Copy constructor
//Vector& Vector::operator=(const Vector& v) {
//	if (this != &v) {
//		delete[] data_ptr;
//		data_ptr = new int[capacity];
//		capacity = v.capacity;
//		n_elems = v.n_elems;
//		for (int i = 0; i < v.size(); i++) {
//			data_ptr[i] = v.at(i);
//		}
//	}
//	return *this;
//} // Copy assignment operator
//Vector::~Vector() {
//	delete[] data_ptr;
//}
//// Accessors
//int Vector::front() const {
//	if (n_elems <= 0) {
//		throw range_error("No elements (front)");
//	}
//	else {
//		return data_ptr[0];
//	}
//}                  // Return the int in position 0, if any
//int Vector::back() const {
//	if (n_elems <= 0) {
//		throw range_error("No elements (back)");
//	}
//	else {
//		return data_ptr[n_elems - 1];
//	}
//}                   // Return last element (position n_elems-1)
//int Vector::at(size_t pos) const {
//	if (n_elems <= 0) {
//		throw range_error("No elements (at)");
//	}
//	else if (pos > (n_elems - 1)) {
//		throw range_error("OOR (at)");
//	}
//	else {
//		return data_ptr[pos];
//	}
//}           // Return element in position "pos" (0-based)
//size_t Vector::size() const {
//	return n_elems;
//}                // Return n_elems
//bool Vector::empty() const {
//	return (n_elems == 0);
//}                 // Return n_elems == 0
//// Mutators
//int& Vector::operator[](size_t pos) {
//	return data_ptr[pos];
//}        // Same as at but no bounds checking
//void Vector::push_back(int item) {
//	if (n_elems == capacity) {
//		grow();
//	}
//	data_ptr[n_elems] = item;
//	n_elems++;
//}           // Append a new element at the end of the array
//void Vector::pop_back() {
//	if (n_elems <= 0) {
//		throw range_error("No elements (pop)");
//	}
//	else {
//		--n_elems;
//	}
//}                    // --n_elems (nothing else to do; returns nothing)
//void Vector::erase(size_t pos) {
//	if (n_elems <= 0) {
//		throw range_error("No elements (erase)");
//	}
//	else if (pos > (n_elems - 1)) {
//		throw range_error("OOR (erase)");
//	}
//	else {
//		for (int i = pos; i < n_elems; i++) {
//			data_ptr[i] = data_ptr[i + 1];
//		}
//		--n_elems;
//		//delete the item?
//	}
//}             // Remove item in position pos and shuffles following items left
//void Vector::insert(size_t pos, int item) {
//	if (n_elems <= 0) {
//		throw range_error("No elements (erase)");
//	}
//	else if (pos > (n_elems - 1)) {
//		grow();
//		for (int i = n_elems; i > pos; i--) {
//			data_ptr[i] = data_ptr[i - 1];
//		}
//		data_ptr[pos] = item;
//		++n_elems;
//	}
//	else if (n_elems == capacity) {
//		push_back(item);
//	}
//	else {
//		for (int i = n_elems; i > pos; i--) {
//			data_ptr[i] = data_ptr[i-1];
//		}
//		data_ptr[pos] = item;
//		++n_elems;
//	}
//}  // Shuffle items right to make room for a new element
//void Vector::clear() {
//	n_elems = 0;
//}                       // n_elems = 0 (nothing else to do; keep the current capacity)
//// Iterators
//int* Vector::begin() {
//	if (n_elems == 0) {
//		return nullptr;
//	}
//	else {
//		return data_ptr;
//	}
//}                       // Return a pointer to 1st element, or nullptr if n_elems == 0
//int* Vector::end() {
//	if (n_elems == 0) {
//		return nullptr;
//	}
//	else {
//		return data_ptr + n_elems;
//	}
//}                         // Return a pointer to 1 past last element, or nullptr if n_elems == 0
//// Comparators
//bool Vector::operator==(const Vector& v) const {
//	if (n_elems == v.size()) {
//		for (int i = 0; i < v.size() && i < n_elems; i++) {
//			if (data_ptr[i] != v.at(i)) {
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//bool Vector::operator!=(const Vector& v) const {
//	return !(*this == v); //Just negate == 
//}