#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Test {
    private:
        //int a;
        int * ptr;
        std::string st;
    public:
        Test(int* a_, std::string st_):ptr(a_),st(st_){}
        ~Test () {cout << "I am in the destruct \n";}
        Test (const Test & copied);// = default;

        Test& operator=(const Test&);// = delete;

        void Show () {
            for (int i = 0; i < 4; i ++) {
                cout << "*ptr" << i<< " = " << *(ptr + i) << endl;
            }
            cout << "ptr = " << ptr << endl;
            cout << "st = " << st << endl;
        }

};


Test::Test (const Test & copied) {
    std::cout << "Test copu funk \n";
    this->ptr = copied.ptr;
    this->st = copied.st;
 }


int main () {

    int m[10];
    int count = 0;
    for (auto &p : m) {
        p = count++;
    }
    
    for (const auto &p : m) {
        std::cout << "m = " << p << std::endl; ;
    }

    int * ptr = &m[5];

    std::cout << *(ptr + 4) << endl;


    std::vector <Test> vek;
    

    for (int i = 0; i < 5; i++) {
        cout << "i = " << i << endl;
        vek.push_back ({&m[i], "Hello " + std::to_string(i)});
    }

    for (int i = 0; i < 5; i++) {
        cout << "i = " << i << endl;
        vek[i].Show ();
        cout << "After Show \n";
    }

    Test  *mas;

    mas = (class Test *)malloc(sizeof(Test)*10);

    for (int i = 0; i < 5; i++) {
        cout << "i = " << i << endl;
        mas[i] = {&m[i], "Hello " + std::to_string(i)};
    }

    mas[2].Show();

    return 0;
}