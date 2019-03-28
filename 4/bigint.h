#ifndef __BIGINT__
#define __BIGINT__
#include <iostream>

class BigInt {
    private:
        char * number = nullptr;
        std::size_t length = 0;
        void string_to_BigInt (const std::string& st);
        //int char_to_Int (char ch);
    public:
        BigInt();
        explicit BigInt(const std::string& st);
        
        BigInt(const BigInt& copied);
        BigInt(const int& copied);
        
        ~BigInt();
        void show () const;
        BigInt& operator=(const BigInt& copied);

        BigInt operator+(const BigInt& other) const;
        


};

#endif