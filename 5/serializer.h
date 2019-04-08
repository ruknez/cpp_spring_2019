
#ifndef __SERIALIZE__
#define __SERIALIZE__

#include <fstream>
#include <type_traits>
#include <typeinfo>

#include "classError.h"

class Serializer {
    private:
        static constexpr char Separator = ' ';
        std::ostream& out_;
    public:
        explicit Serializer(std::ostream& out);

            template <class T>
            Error save(T& object);

            template <class... ArgsT>
            Error operator()(ArgsT... args);

    private:
        template <class T>
        Error process (T&& val);


        template <class T, class... ArgsT>
        Error process (T&& val, ArgsT&&... args);

        Error typedefimition (void* ptr);

        Error typedefimition(bool* t);

        Error typedefimition(uint64_t* t);

        template <class T>
        void print(T&& val) {
            std::cout << "val in print (T&& val) = " << val << '\n';
        }

        template <class T, class... ArgsT>
        void print (T&& val, ArgsT&&... args);


};

#include "serializer.cpp"

#endif