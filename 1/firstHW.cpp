#include <iostream>

//#define VECTOR

#ifdef VECTOR
    #include <vector>
    #include <algorithm>
#else
    #include <set>
#endif

#include "numbers.dat"

int find_first_number (int number);
int find_second_number (int number);
#ifdef VECTOR
    void eratosthenes (std::vector <int> &a);
#else
    std::set <int> eratosthenes ();
#endif

int main(int argc, char* argv[]) {

    if ((argc - 1) % 2 != 0 || argc == 1) {
        return -1;
    }
#ifdef VECTOR
    std::vector <int> simp_num;// (Size + 1);
    eratosthenes(simp_num);
#else
    std::set <int> simp_num = eratosthenes();
#endif

    for (int i = 1; i < argc; i+=2) {
        
        int first_number = find_first_number(std::atoi(argv[i]));
        int second_number = find_second_number(std::atoi(argv[i + 1]));

        int count = 0;
        for (int i = first_number; i <= second_number; i++) {
#ifdef VECTOR            
           if (std::count (begin (simp_num), end (simp_num), Data[i])) {
               count++;
           }
#else
            if (simp_num.count(Data[i])) {
                count++;
            }
#endif
        }
        std::cout << count << std::endl;
    }

    return 0;
}

//=====================================================
int find_first_number (int number) {
    
    for (int i = 0; i < Size; ++i) {
        if (Data[i] == number) {
            return i;
        }
    }

    return -1;
}

//=====================================================
int find_second_number (int number) {
    
    for (int i = Size - 1;  i >= 0; --i) {
        if (Data[i] == number) {
            return i;
        }
    }

    return -1;
}

//=====================================================
#ifdef VECTOR
    void eratosthenes (std::vector <int> &vec) {
#else
    std::set <int> eratosthenes () {
#endif

    int *a = new int [Size + 1];

    for (int i = 0; i <= Size; ++i) {
        a[i] = i;
    }

    for (int i = 2; i * i <= Size; ++i) {
        if (a[i]) {
            for (int j = i*i; j <= Size; j+=i) {
                a[j] = 0;
            }
        }
    }
#ifndef VECTOR
    std::set <int> simp_num;
#endif

    for (int i = 2; i < Size; i++) {
        if (a[i]) {
#ifdef VECTOR
            vec.push_back(a[i]);
#else
            simp_num.insert(a[i]);
#endif
          
        }
    }

    delete[] a;
#ifndef VECTOR
    return simp_num;
#endif
}



