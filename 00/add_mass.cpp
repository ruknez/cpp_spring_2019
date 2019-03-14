#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <chrono> /* for timer */


using std::cout;
using std::endl;

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};


int main() {
    const int size = 1000;
    int **my_mass  = new int* [size];
    for (int i = 0; i < size; i++) {
        my_mass[i] = new int [size];
    }

 
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            my_mass[j][i] = rand() % 100;
        }
    }

    long long int sum = 0;
{
    Timer t;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sum += my_mass[i][j];
            //cout <<  my_mass[i][j] << " ";
        }
        //cout << '\n';
    }
}

{
    Timer t;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sum += my_mass[j][i];
            //cout <<  my_mass[i][j] << " ";
        }
        //cout << '\n';
    }
}

cout << "\n\n";

    for (int i = 0; i < size; i++) {
        delete [] my_mass[size];
    }

    return sum;
}