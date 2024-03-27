/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA6
 * BigInteger.cpp
 * Source Code for BigInteger ADT
 * ***************************************************************************/
#include "BigInteger.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

// global constants (set for proper grading)
const long base = 1000000000; // 1 billion
const int power = 9; 

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0; // 1, -1, 0 for pos, neg, zero
    digits = List(); // List for digits
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
    long num = (x > 0) ? x : -x;
    if (x > 0) { // if long is positive
        signum = 1; // set sign as pos
        while (num > 0) { // while digits left to parse
            ListElement curr = fmod(num, 10); // get curr digit at end
            digits.insertAfter(curr); // add curr digit to List
            num /= 10; // update num
        }
    }
    else if (x < 0) { // if long is negative
        signum = -1; // set sign as neg
        num *= -1;
        while (num > 0) { // while digits left to parse
            ListElement curr = fmod(num, 10); // get curr digit at end
            digits.insertAfter(curr); // add curr digit to List
            num /= 10; // update num
        }
    }
    else { // if long is zero
        signum = 0;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) { // check if string is empty
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if (s.find_first_of("-+") == 0) { // check if string has sign
        std::string nosign = s.substr(1, s.length() - 1); // get string without sign
        if (nosign.find_first_not_of("0123456789") != std::string::npos) { // check for invalid char in string
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    else { // no sign, still check for invalid char in string
        if (s.find_first_not_of("0123456789") != std::string::npos) { 
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    // check for sign
    if (s[0] == '+') { // string is signed pos
        //cout << "got here" << endl;
        s = s.substr(1);
        signum = 1;
    }
    else if (s[0] == '-') { // string is signed neg
        //cout << "got here" << endl;
        s = s.substr(1);
        signum = -1;
    }
    else { // string is unsigned pos
        //cout << "got here no sign" << endl;
        signum = 1; 
    }

    // add digits to List
    // NOTE TO SELF: we're working from right to left and parsing 9 chars at a time,
    // we separate the string into groups of p chars (9) and the final, leftmost base
    // b may be less than p (9)
    int grp = s.length()/ power; // get number of groups in string
    for (int i = s.length(); grp >= 0; grp -= 1) { // looping thru groups
        //cout << "got here 3" << endl;
        if (grp > 0) { // if there are groups left in string
            long d = std::stol(s.substr(i - power, power));
            digits.insertAfter(d); 
            i -= power;
        }
        else if ((s.length() % power) != 0) {  // check for final, leftmost digits (< 9)
            long d = std::stol(s.substr(0, s.length() % power));
            digits.insertAfter(d);
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (sign() > N.sign()) { // base cases to check for
        return 1;
    }
    else if (sign() < N.sign()) {
        return -1;
    }
    else if (this->digits.length() > N.digits.length()) {
        return signum;
    }
    else if (this->digits.length() < N.digits.length()) {
        return signum * -1;
    }
    List this_list = this->digits;
    List N_list = N.digits;
    // loop thru digits of this and N, comparing each 
    for (this_list.moveFront(), N_list.moveFront(); this_list.position() < this_list.length(); this_list.moveNext(), N_list.moveNext()) {
        if (this_list.peekNext() < N_list.peekNext()) {
            return -1;
        }
        else if (this_list.peekNext() > N_list.peekNext()) {
            return 1;
        }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear(); // clear List of digits
    signum = 0; // BigInt is now just 0
}  

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    signum *= -1; // reverse sign of BigInt (signum)
}

// BigInteger Arithmetic operations ----------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    for (L.moveBack(); L.position() > 0; L.movePrev()) { // loop thru list
        L.setBefore(L.peekPrev() * -1); // negate each element
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    long currA, currB;
    S.clear();
    A.moveBack(); // working from right to left
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) { // loop thru A and B
        currA = A.movePrev();
        currB = B.movePrev();
        S.insertAfter(currA + (sgn * currB)); // add A + sgn * B
    }
    while (A.position() > 0) { // if there are elements left in A
        currA = A.movePrev();
        S.insertAfter(currA); // add digit currA 
    }
    while (B.position() > 0) { // if there are elements left in B
        currB = B.movePrev();
        S.insertAfter(sgn * currB); // add digit currB
    }
    for (S.moveFront(), S.moveNext(); S.length() > 1 && S.front() == 0; S.moveNext()) { // delete leading zeros
        S.eraseBefore();
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
// CITE: Partially written with help of Tutor Norton Choy (main loop)
int normalizeList(List& L) {
    int sign = 1;
    L.moveFront();
    if (L.peekNext() < 0) {
        negateList(L);
        sign = -1;
    }
    else if (L.peekNext() == 0) {
        return 0;
    }
    ListElement num = 0;
    int carry = 0;
    L.moveBack(); // move cursor to back
    while (L.position() > 0) { // looping until front of list
        num = L.peekPrev(); // get curr num
        if (num < 0) { // if curr num is neg
            num += base + carry;
            carry = -1; // since num is neg, carry is -1
            L.setBefore(num); // set updated num
        }
        else { // curr num is pos
            num += carry; // before fixing base
            carry = 0;
            if (num >= base) {
                carry = num/base;
                num = num % base;
            }
            L.setBefore(num); // update new num
        }
        L.movePrev();
        if (carry != 0 && L.position() == 0) { // if at front and still have carry
            L.insertAfter(carry); // insert carry
        }
    }
    return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) { // prepend p zero digits
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    //for (L.moveFront(); L.position() < L.length(); L.moveNext()) { // looping thru list
    //    L.setAfter(m * L.peekNext()); // update element after cursor * m
    //}
    for (L.moveBack(); L.position() > 0; L.movePrev()) { // from right to left
        L.setBefore(m * L.peekPrev()); // update element before cursor * m
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum;
    List sumlist;
    if (sign() == 1 && N.sign() == 1) { // if this pos and N pos
        sumList(sumlist, this->digits, N.digits, 1); // A + B
        sum.signum = normalizeList(sumlist); 
        sum.digits = sumlist;
    }
    else if (sign() == -1 && N.sign() == -1) { // if this neg and N neg
        List thisD = this->digits;
        negateList(thisD); // this = -this
        sumList(sumlist, thisD, N.digits, -1); // -A + (-B)
        sum.signum = normalizeList(sumlist);
        sum.digits = sumlist;
    }
    else if (sign() == 1 && N.sign() == -1) { // if this pos and N neg
        sumList(sumlist, this->digits, N.digits, -1); // A + (-B)
        sum.signum = normalizeList(sumlist);
        sum.digits = sumlist;
    }
    else if (sign() == -1 && N.sign() == 1) { // if this neg and N pos
        sumList(sumlist, N.digits, this->digits, -1); // B + (-A)
        sum.signum = normalizeList(sumlist);
        sum.digits = sumlist;
    }
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger D(*this); // D = this
    BigInteger S(N);
    negateList(S.digits); // S = -N
    return D.add(S); // return (D + S) = (this - N)
}

// mult()
// Returns a BigInteger representing the product of this and N. 
// NOTE TO SELF: First, check if we're multiplying by 0, and return empty BigInt if true.
// Second, in our main loop we account for shifting when multiplying higher place digit (need shift index).
// Shift -> ScalarMult -> Sum (add to new BigInt as we go) -> Normalize 
// ^ (follow this structure as we multiply every digit of N to digits of this)
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger A (*this); // copy of this
    BigInteger B (N); // copy of N
    BigInteger prod; // BigInt to be returned
    if (sign() == 0 || N.sign() == 0) { // check if this or N are 0
        return prod;
    }
    List digsA = A.digits; // digits of this (copy)
    List digsB = B.digits; // digits of N (copy)
    int to_shift = 0; // index for shifting (accounting for multiplying)
    for (digsB.moveBack(); digsB.position() > 0; digsB.movePrev(), to_shift += 1) { // loop thru digits in N, updating shift index as we go
        digsA.clear(); // clean out digits of A
        digsA = A.digits; // reset digits of A as this->digits, since it gets changed from shift/scalarmult
        shiftList(digsA, to_shift); // shift by approp. amount
        scalarMultList(digsA, digsB.peekPrev()); // get list * curr digit in N
        sumList(prod.digits, prod.digits, digsA, 1); // prod.digits += digits of A (add as we go)
        normalizeList(prod.digits); // normalize as we go
    }

    // set sign for new prod
    if (sign() != N.sign()) {
        prod.signum = -1;
    }
    else {
        prod.signum = 1;
    }
    return prod;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    if (sign() == 0) { // check if num is 0
        return "0";
    }
    std::string s = ""; // init empty str
    if (sign() == -1) { // if BigInt is neg
        s += "-";
    }
    digits.moveFront();
    while (digits.position() < digits.length()) { // looping through digits
        std::string curr = std::to_string(digits.moveNext());
        if (digits.position() > 1) {
            while (power > curr.length()) { // while len of curr element is < power
                curr = "0" + curr; // fill in leading zero
            }
            s += curr;
        }
        else {
            s += curr;
        }
    }
    return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::compare(B) != 1;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) { 
    return A.BigInteger::compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::compare(B) != -1;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}