#pragma once
#include <cassert>
#include <iostream>
#include <bitset>


class Bits {
    using IType = unsigned long long; // We only have to change the integer type here, if desired
    enum { NBITS = sizeof(IType) * 8 };
    IType bits = 0;
public:
    Bits() = default;
    Bits(IType n) {
        bits = n;
    }
    static int size() {
        return NBITS;
    }
    bool at(int pos) const {  // Returns (tests) the bit at bit-position pos
        assert(0 <= pos && pos < NBITS);
        return bits & (IType(1) << pos);
    }
    void set(int pos) {        // Sets the bit at position pos
        bits |= (1 << pos);
    }
    void set() {               // Sets all bits
        for (int i = 0; i < size(); i++) {
            bits |= (1 << i);
        }
    }
    void reset(int pos) {      // Resets (makes zero) the bit at position pos
        bits &= ~(1 << pos);
    }
    void reset() {             // Resets all bits
        for (int i = 0; i < size(); i++) {
            bits &= ~(1 << i);
        }
    }
    void assign(int pos, bool val) { // Sets or resets the bit at position pos depending on val
        if (val) {
            set(pos);
        }
        else {
            reset(pos);
        }
    }
    void assign(IType n) {     // Replaces the underlying integer with n
        bits = n;
    }
    void toggle(int pos) {     // Flips the bit at position pos
        bits ^= (1 << pos);
    }
    void toggle() {            // Flips all bits
        for (int i = 0; i < NBITS; i++) {
            bits ^= (static_cast<unsigned long long>(1) << i);
        }
    }
    void shift(int n) {        // If n > 0, shifts bits right n places; if n < 0, shifts left
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                bits = IType(bits >> 1);
            }
        }
        else if (n < 0) {
            for (int i = 0; i > n; i--) {
                bits = IType(bits << 1);
            }
        }
    }
    void rotate(int n) {       // If n > 0, rotates right n places; if n < 0, rotates left
        if (n > 0) {
            IType temp = bits >> n | bits << (size() - n);
            bits = temp;
            //bits = IType(bits >> n | bits << (size() - n));
        }
        else if (n < 0) {
            //IType temp1 = IType(bits << n);
            //IType temp2 = IType(bits >> (32 - n));
            //bits = temp1 | temp2;
            n *= -1;
            IType temp = IType(bits << n | bits >> (size() - n));
            bits = temp;
        }
    }
    int ones() const {         // Returns how many bits are set in the underlying integer
        int count = 0;
        IType temp = bits;
        while (temp != 0) {
            if (temp & 1 == 1) {
                count++;
            }
            temp = IType(temp >> 1);
        }
        return count;
    }
    int zeroes() const {      // Returns how many bits are reset in the underlying integer
        return NBITS - ones();
    }

    IType to_int() const {
        return bits;
    }
    friend bool operator==(const Bits& b1, const Bits& b2) {
        return b1.bits == b2.bits;
    }
    friend bool operator!=(const Bits& b1, const Bits& b2) {
        return b1.bits != b2.bits;
    }
    friend std::ostream& operator<<(std::ostream& os, const Bits& b) {
        return os << std::bitset<NBITS>(b.bits);    // Be sure to #include <bitset>
    }
};