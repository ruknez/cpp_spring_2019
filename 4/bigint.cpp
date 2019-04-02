#include <iostream>
#include <string>
#include <stdlib.h> 

using std::size_t;

#include "bigint.h"


const int aski_shift = 48; /*приведение char к int дает ASCII код символа, а не переводит '1' в 1 */



BigInt::BigInt (const std::string& st) {
    string_to_BigInt (st);
}


void BigInt::string_to_BigInt (const std::string& st) {
    
    if (number != nullptr) {
        delete[] number;
    }
    std::string new_st = st;
    int count =0;

    if (st[0] == '-') {
        isNeg = true;
        count++;
        //new_st = st.substr(1);
    }
    for (;count < st.length();) {
        if (st[count] != '0') {
            break;
        }
        count++;
    }

    new_st = st.substr(count);
    length = new_st.length();
  
    if (length == 0) {
        length = 1;
        number = new char [1];
        number[0] = '0'; 
    } else {
        number = new char [length];
    
        for (size_t i = 0; i < length; i++) {
            /*
            std::cout << "i = " << i << "  ";
            std::cout << "st = " <<  st [i] << std::endl; */
            number [length - 1 - i] = new_st [i];
        } 
    }
}

BigInt::BigInt () {
    length = 1;
    number = new char [1];
    number[0] = static_cast <char> (0 + aski_shift);
    isNeg = false;

}

BigInt::BigInt(long x) {
    //this->isNeg = x < 0;
    string_to_BigInt (std::to_string (x));
}
        

BigInt::~BigInt () { 
    delete [] number;
}

 void BigInt::del_zero (BigInt& bigint) const {
    size_t count = 0;

    for (size_t i = 0;i < bigint.length; i++) {
        if (bigint.number[bigint.length - i - 1] != '0') {
            break;
        }
        count++;
    }

    if (count == 0) {
        return;
    }

    if (count == bigint.length) {
        delete [] number;
        bigint.length = 1;
        bigint.number = new char [1];
        bigint.number[0] = '0'; 
    } else {
        char * ptr = new char [bigint.length - count];
        std::copy (bigint.number, bigint.number + (bigint.length - count), ptr);
        delete [] bigint.number;
        bigint.length = (bigint.length - count);
        bigint.number = new char [bigint.length];
        std::copy (ptr, ptr + bigint.length, bigint.number);
    }



 }

std::string BigInt::show ()const {

    std::string st = (isNeg) ? "-" : "";
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
    isNeg = copied.isNeg;
    std::copy (copied.number, copied.number + length, number);
    return *this;
}

// конструктор копирования
BigInt::BigInt(const BigInt& copied):number(new char [copied.length]),length(copied.length),isNeg(copied.isNeg) {
    std::copy (copied.number, copied.number + length, number);
}

BigInt::BigInt(int copied) {
    std::string st = std::to_string (copied);
    string_to_BigInt (st);
}

int char_to_int (char ch) {
    return (static_cast<int> (ch) - aski_shift);
}

BigInt BigInt::operator-() const {
    BigInt tmp = *this;
    tmp.isNeg = !isNeg;
    return tmp;
}


BigInt BigInt::operator+(const BigInt& other) const {

    if (isNeg == other.isNeg) {
        
        BigInt tmp;
        tmp.length = std::max (other.length,length);
        tmp.number = new char [tmp.length];
        tmp.isNeg = isNeg;

        int rem_div = 0;

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
            tmp.number [i] = static_cast <char> (int_div + aski_shift);
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
    } else {
        return  (isNeg) ? (other - (-BigInt(*this))) : (*this - (-BigInt(other)));
    } 
}

bool BigInt::operator==(const BigInt& rhs) const {
    if (this->length == 1 && rhs.length == 1) {
        if (this->number[0] == '0' && rhs.number[0] == '0') {
            return true;
        }
    }

    if (this->length == rhs.length && this->isNeg == rhs.isNeg) {
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


    if (this == &rhs || *this == rhs) {
        return false;
    }

    
    if (isNeg == rhs.isNeg) {
        
        if (this->length != rhs.length) {
            return (this->length < rhs.length) ^ isNeg;
        }
    
        for (int i = length -1; i >= 0; i--) {
            if (number[i] != rhs.number[i]) {
                return ((number[i] < rhs.number[i]) ^ isNeg);
            }
        }
    }

    return  isNeg;
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
    return !(*this == rhs);
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


BigInt BigInt::operator-(const BigInt& other) const {
    if (this == &other) {
        return 0;
    }

    if (!isNeg && !other.isNeg) {
       

        size_t len1 = length;
        size_t len2 = other.length;
        size_t max_lenght = std::max(len1,len2);

        bool isNegRes = other > *this; 

        int a[max_lenght];
        int b[max_lenght];
        int c[max_lenght];

        c[0] = a[0] = b[0] = 0;

        BigInt tmp;
        tmp.length = max_lenght;
        tmp.isNeg = isNegRes;
        tmp.number = new char [tmp.length];

        int sign = (2 * isNegRes - 1);

        for (size_t i = 0; i < max_lenght - 1; i++) {
            a[i] += (length > i)?char_to_int (number[i]):0;
            b[i] += (other.length > i)?char_to_int (other.number[i]):0;

            b[i + 1] = -isNegRes;
            a[i + 1] = isNegRes - 1;

            c[i] += 10 + sign * (b[i] - a[i]);
            c[i + 1] = c[i] / 10;
            c[i] = c [i] % 10 + 0;

            tmp.number[i] = static_cast <char>(c[i] + aski_shift);
        }

        a[max_lenght - 1] += (max_lenght - 1 < len1) * (length > max_lenght-1)?char_to_int (number[max_lenght-1]):0;;
		b[max_lenght - 1] += (max_lenght - 1 < len2) * (other.length > max_lenght-1)?char_to_int (other.number[max_lenght-1]):0;
        c[max_lenght - 1] +=  sign * (b[max_lenght - 1] - a[max_lenght - 1]) + 0;
        
        for (size_t i = 0; i < max_lenght - 1; i++) {
            if (c[max_lenght - 1 - i] == 0) {
                tmp.length--;
                continue;
            }
            break;
        }
/*
        if (c[max_lenght - 1] == 0 && max_lenght > 1) {
            tmp.length--;
        }
*/
        tmp.number[max_lenght - 1] = static_cast <char>(c[max_lenght - 1] + aski_shift);
        

        //del_zero(tmp);

        return tmp;
    } else {
        return (isNeg && other.isNeg) ? (-BigInt(other) - (-BigInt(*this))) :(*this + -BigInt(other));
    }
}
