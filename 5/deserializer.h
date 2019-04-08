#ifndef __DESERIALIZER__
#define __DESERIALIZER__

#include <fstream>
#include <type_traits>
#include <typeinfo>
#include <limits>

#include "classError.h"

class Deserializer {
     private:
        std::istream& in_;
    public:
        explicit Deserializer(std::istream& in);

        template <class T>
        Error load(T& object);

        template <class... ArgsT>
        Error operator()(ArgsT&... args);

    private:
        template <class T>
        Error process (T& val);

        template <class T, class... ArgsT>
        Error process (T& val, ArgsT&&... args);

        Error deservalue (bool& value);
        Error deservalue (uint64_t& value);

};

#include "deserializer.cpp"

#endif