#ifndef __BIGINT__
#define __BIGINT__
#include <iostream>

class BigInt {
    private:
        char * number = nullptr;
        std::size_t length = 0;
        bool isNeg = false;

        void string_to_BigInt (const std::string& st);

        void del_zero (BigInt& bigint) const;
        //int char_to_Int (char ch);
    public:
        BigInt();
        explicit BigInt(const std::string& st);
        
        BigInt(const BigInt& copied);
        BigInt(int copied);
        BigInt(long x);

        ~BigInt();
        std::string show () const;
        BigInt& operator=(const BigInt& copied);

        BigInt operator-() const;

        BigInt operator+(const BigInt& other) const;
        BigInt operator-(const BigInt& other) const;

        bool operator==(const BigInt& rhs) const;
        bool operator< (const BigInt& rhs) const;
        bool operator> (const BigInt& rhs) const;
        bool operator<=(const BigInt& rhs) const;
        bool operator>=(const BigInt& rhs) const;
        bool operator!=(const BigInt& rhs) const;
        
        //std::ostream& operator << (std::ostream& stream);
};

std::ostream& operator << (std::ostream& stream, const BigInt& bigint);

#endif
