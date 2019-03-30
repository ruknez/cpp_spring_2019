#include <iostream>
#include <string>
#include <stdlib.h> 

using std::size_t;

#include "bigint.h"


BigInt::BigInt (const std::string& st) {
    string_to_BigInt (st);
}


void BigInt::string_to_BigInt (const std::string& st) {
    
    if (number != nullptr) {
        delete[] number;
    }

    length = st.length();
    number = new char [length];


    for (size_t i = 0; i < length; i++) {
        /*std::cout << "i = " << i << "  ";
        std::cout << "st = " <<  st [i] << std::endl;*/
        number [length - 1 - i] = st [i];
    }

    
}

BigInt::BigInt ():number(nullptr),length(0) {}

BigInt::~BigInt () { 
    delete [] number;
}

std::string BigInt::show ()const {

    std::string st = "";
    for (size_t i = 0; i < length; i++) {
        st += number[length - 1 - i];
    }
    return st;
}

BigInt& BigInt::operator=(const BigInt& copied) {
    if (this == &copied) {
        return *this;
    }

    char * ptr = new char [copied.length];
    delete[] number;
    number = ptr;
    length = copied.length;
    std::copy (copied.number, copied.number + length, number);
    return *this;
}

// конструктор копирования
BigInt::BigInt(const BigInt& copied):number(new char [copied.length]), length(copied.length) {
    std::copy (copied.number, copied.number + length, number);
}

BigInt::BigInt(const int& copied) {
    std::string st = std::to_string (copied);
    string_to_BigInt (st);
}

int char_to_int (char ch) {
    return (static_cast<int> (ch) - 48);
}


BigInt BigInt::operator+(const BigInt& other) const {
    BigInt tmp;

    if (other.length >= this->length) {
        tmp.length = other.length;
        std::cout << __LINE__ << std::endl;
    } else {
        tmp.length = length;
    }
    
    tmp.number = new char [tmp.length];

    int rem_div = 0; //(char_to_int(number[0]) + char_to_int(other.number[0])) / 10;

    for (size_t i = 0; i < tmp.length; i++) {
        
        int lval = 0;
        int rval = 0; 
        
        if (other.length > i) {
            rval = char_to_int (other.number[i]);
        }
        if (length > i) {
            lval = char_to_int (number[i]);
        }

        int int_div = (lval + rval + rem_div) % 10;
        tmp.number [i] = static_cast <char> (int_div + 48);
        rem_div = (lval + rval + rem_div) / 10;
    }

    if (rem_div) {
        char * ptr = new char [tmp.length];
        std::copy (tmp.number, tmp.number +tmp.length, ptr);
        delete [] tmp.number;
        tmp.length++;
        tmp.number = new char [tmp.length];
        std::copy (ptr, ptr + tmp.length - 1, tmp.number);
        tmp.number [tmp.length -1]  = '1'; 
    }

    return tmp;
}

bool BigInt::operator==(const BigInt& rhs) const {

    if (this->length == rhs.length) {
        for (size_t i = 0; i < this->length; i++) {
            if (this->number[i] != rhs.number[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}


bool BigInt::operator<(const BigInt& rhs) const {

    if (this->length < rhs.length) {
        return true;
    }
    if (this->length > rhs.length || this == &rhs || *this == rhs) {
        return false;
    }
    
    if (this->length == rhs.length) {
        for (int i = length -1; i >= 0; i--) {
            if (number[i] < rhs.number[i]) {
                return true;
            } else if (number[i] > rhs.number[i]) {
                return false;
            }
        }
    }

    return  true;
}


bool BigInt::operator>(const BigInt& rhs) const {
    if (*this == rhs || *this < rhs) {
        return false;
    }
    return true;
}

bool BigInt::operator<=(const BigInt& rhs) const {
    if (*this == rhs || *this < rhs) {
        return true;
    }
    return false;
}

bool BigInt::operator>=(const BigInt& rhs) const {
    if (*this == rhs || *this > rhs) {
        return true;
    }
    return false;
}

bool BigInt::operator!=(const BigInt& rhs) const {
    if (*this == rhs) {
        return false;
    }
    return true;
}


/*
std::ostream& BigInt::operator << (std::ostream& stream) {
    std::cout << "I am in BigInt::operator \n";
    for (size_t i = 0; i < length; i++) {
        stream << number[length - 1 - i];
    }
    return stream;
}
*/

std::ostream& operator << (std::ostream& stream, const BigInt& bigint) {
    stream << bigint.show ();
    return stream;
}

/*
BigInt BigInt::operator-(const BigInt& other) const {
    BigInt tmp;

    if (other.length >= this->length) {
        tmp.length = other.length;
    } else {
        tmp.length = length;
    }
    
    tmp.number = new char [tmp.length];

    for (size_t i = 0; i < tmp.length; i++) {

    }

    return tmp;
}
*/