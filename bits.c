/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(~x&~y)) & (~(x&y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x && !y)return 1;
    if(!x && y)return 0;
    if(x && !y)return 0;
    return !((x^y)>>31)&1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res = 0;
    int shift;

    shift = (v > 0xFFFF) << 4;  
    res = res | shift;
    v = v >> shift;
    shift = (v >0xFF) << 3;
    res = res | shift;
    v = v >> shift;
    shift = (v >0xF) << 2;
    res = res | shift;
    v = v >> shift;
    shift = (v >0x3) << 1;
    res = res | shift;
    v = v >> shift;
    shift = v > 1;
    res = res | shift;

    return res;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a = n<<3;
    int b = m<<3;
    int temp1 = ((x>>a)&0xFF)<<b;
    int temp2 = ((x>>b)&0xFF)<<a;
    int clear = (0xFF << a) | (0xFF<<b);
    return (x & ~clear) | temp1 | temp2;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned temp1 = v & 0xFFFF;
    unsigned res1 = (temp1<<16) | (v>>16);
    unsigned res2 = ((res1 & 0xFF00FF00)>>8) | ((res1 & 0x00FF00FF)<<8);
    unsigned res3 = ((res2 & 0xF0F0F0F0)>>4) | ((res2 & 0x0F0F0F0F)<<4);
    unsigned res4 = ((res3 & 0xCCCCCCCC)>>2) | ((res3 & 0x33333333)<<2);
    unsigned res5 = ((res4 & 0xAAAAAAAA)>>1) | ((res4 & 0x55555555)<<1);
    return res5;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int temp = 0x80000000;
    int mask = ~(temp >> n << 1);
    int res = (x>>n)&mask;
    return res;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int res = 0;
    int shift = 0;
    shift = (!~(x>>16))<<4;
    res += shift;
    x = x<<shift;

    shift = (!~(x>>24))<<3;
    res += shift;
    x = x<<shift;

    shift = (!~(x>>28))<<2;
    res += shift;
    x = x<<shift;

    shift = (!~(x>>30))<<1;
    res += shift;
    x = x<<shift;

    shift = (!~(x>>31));
    res += shift;
    x = x<<shift;

    shift = (!~(x>>31));
    res += shift;

    return res;
}


/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign, ux, exp, frac, shift, tail;

    if (x == 0) return 0;
    sign = 0;
    if (x < 0) { sign = 1 << 31; x = -x; }
    ux = x;

    exp = 0;
    if (ux >> 16) { exp += 16; ux >>= 16; }
    if (ux >>  8) { exp +=  8; ux >>=  8; }
    if (ux >>  4) { exp +=  4; ux >>=  4; }
    if (ux >>  2) { exp +=  2; ux >>=  2; }
    if (ux >>  1) { exp +=  1; }
    ux = x; if (x < 0) ux = ~(unsigned)x + 1;

    if (exp < 24) return sign | ((exp + 127) << 23) | ((ux << (23 - exp)) & 0x7fffff);

    shift = exp - 23;
    frac  = ux >> shift;
    tail  = ux << (32 - shift);
    frac += (tail >> 31) & ((tail << 1) | (frac & 1));
    if (frac >> 24) { frac = 1 << 23; exp++; }
    return sign | ((exp + 127) << 23) | (frac & 0x7fffff);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    if (exp == 0xFF) {
        return uf;
    }
    if (exp == 0) {
        return (uf & 0x80000000) | (uf << 1);
    }
    return uf + (1 << 23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    
    if (exp < 1023) {
        return 0;
    }
    if (exp >= 1054) {
        return 0x80000000;
    }
    
    unsigned shift = exp - 1023;
    unsigned high = (uf2 & 0xFFFFF) | 0x100000;
    unsigned low = uf1;
    unsigned result;
    
    if (shift <= 20) {
        result = high >> (20 - shift);
    } else {
        result = (high << (shift - 20)) | (low >> (52 - shift));
    }
    
    if (sign) {
        return ~result + 1;
    }
    
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x >= 128) {
        return 0x7F800000;
    }
    
    if (x >= -126) {
        int exp = x + 127;
        return exp << 23;
    }
    
    if (x >= -149) {
        return 1 << (x + 149);
    }
    
    return 0;
}
