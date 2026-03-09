
#pragma once

inline int ilog2_int(int x) {
    unsigned int u = static_cast<unsigned int>(x);
    int pos = -1;
    while (u) {
        u >>= 1;
        ++pos;
    }
    return pos;
}

inline int ilog2_float(float x) {
    union {
        float f;
        unsigned int u;
    } converter;
    converter.f = x;
    unsigned int bits = converter.u;
    int exp = (bits >> 23) & 0xFF;
    unsigned int mant = bits & 0x7FFFFF;
    if (exp == 255) {
        return 128;
    }
    if (exp == 0) {
        if (mant == 0) {
            return -128;
        }
        int pos = -1;
        while (mant) {
            mant >>= 1;
            ++pos;
        }
        return pos - 149;
    }
    return exp - 127;
}

