
Serializer::Serializer (std::ostream& out):out_(out) {}

template <class T>
Error Serializer::save(T& object) {
    return object.serialize (*this);
}


template <class... ArgsT>
Error Serializer::operator()(ArgsT... args) {
    return process(args...);
}

template <class T, class... ArgsT>
void Serializer::print (T&& val, ArgsT&&... args) {
    print(std::forward<ArgsT>(args)...);
}


template <class T>
Error Serializer::process (T&& val) {
    //int a = 0;
    //std::cout << std::is_same<std::typeof(a) uint64_t>::value << std::endl;   
    return  typedefimition (&val);
}

template <class T, class... ArgsT>
Error Serializer::process(T&& val, ArgsT&&...args) {
    
/*    
    //std::is_integral<char>::value
    std::cout << std::is_same<int, uint64_t>::value << std::endl;
    char a = 0;
    std::cout << "std::typeid(a).name() = " << typeid(val).name() << std::endl;
    std::cout << "val process2 =  " << val << std::endl; 
*/
    if (typedefimition (&val) == Error::CorruptedArchive) {
        return Error::CorruptedArchive;
    }
  //  print(args...);
    return  process (std::forward<ArgsT>(args)...);
}

Error Serializer::typedefimition (void* ptr) {
    return Error::CorruptedArchive;
}

Error Serializer::typedefimition(bool* t) {

    if (*t) {
        out_ << "true" << Separator;
    } else {
         out_ << "false" << Separator;
    }
    //std::cout << "out_ = " << out_ << std::endl;
    return Error::NoError;
}

Error Serializer::typedefimition(uint64_t* t) {
    out_ << *t << Separator;
    return Error::NoError;
}

