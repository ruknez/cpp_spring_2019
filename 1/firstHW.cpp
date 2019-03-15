#include <iostream>
#include <set>

#include "numbers.dat"

int find_element_number (int number);
std::set <int> eratosthenes ();

int main(int argc, char* argv[]) {

    if ((argc - 1) % 2 != 0 || argc == 1) {
        return -1;
    }

    std::set <int> simp_num = eratosthenes();

    for (int i = 1; i < argc; i+=2) {
        
        int first_number = find_element_number(std::atoi(argv[i]));
        int second_number = find_element_number(std::atoi(argv[i + 1]));

        int count = 0;
        for (int i = first_number; i <= second_number; i++) {
            if (simp_num.count(Data[i])) {
                count++;
            }
        }
        std::cout << count << std::endl;
    }

    return 0;
}


//=====================================================
int find_element_number (int number) {
    
    for (int i = 0; i < Size; ++i) {
        if (Data[i] == number) {
            return i;
        }
    }

    return -1;
}

//=====================================================
std::set <int> eratosthenes () {

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

    std::set <int> simp_num;
    for (int i = 2; i < Size; i++) {
        if (a[i]) {
            simp_num.insert(a[i]);
        }
    }

    delete[] a;
    return simp_num;
}



