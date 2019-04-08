#pragma once
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
        Error operator()(ArgsT&&... args);

    private:
        template <class T>
        Error process (T&& val);

        template <class T, class... ArgsT>
        Error process (T&& val, ArgsT&&... args);

        Error deservalue (bool& value);
        Error deservalue (uint64_t& value);
};


Deserializer::Deserializer (std::istream& in):in_(in) {}

template <class T>
Error Deserializer::load(T& object) {
    return object.serialize (*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&&... args) {
    return process(std::forward<ArgsT>(args)...);
}

template <class T>
Error Deserializer::process (T&& val) {
    return deservalue (std::forward<T>(val));
}

template <class T, class... ArgsT>
Error Deserializer::process (T&& val, ArgsT&&... args) {
    if (deservalue (std::forward<T>(val)) == Error::CorruptedArchive) {
        return Error::CorruptedArchive;
    }
    return  process (std::forward<ArgsT>(args)...);
}

Error Deserializer::deservalue (bool& value) {
    std::string text;
    in_ >> text;

    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}

 Error Deserializer::deservalue (uint64_t& value) {
    long long int num;
    in_ >> num;
    
    if (num < 0 || num > std::numeric_limits<uint64_t>::max()) {
        return Error::CorruptedArchive;
    }

/*
    std::cout << std::numeric_limits<uint64_t>::min() << std::endl;
    std::cout << std::numeric_limits<uint64_t>::max() << std::endl << std::endl;
    std::cout << std::numeric_limits<long long int>::min() << std::endl;
    std::cout << std::numeric_limits<long long int>::max() << std::endl << std::endl;
*/
    value =  num ;

    return Error::NoError;
}


#endif