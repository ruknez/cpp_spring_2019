#ifndef __MATRIX__
#define __MATRIX__
#include <vector>
class Matrix {
    class Column {
        private: 
            int*  pRow;
            std::size_t cols;
        public:
            const int& operator[](int i) const;
            int& operator[] (int i);
            int Getnumber (size_t num) const;
            void Changenumb (size_t num, int val);
            Column (const Column&); //= delete;
            Column& operator=(const Column&) = delete;

            Column(int *ptr, size_t size);
            ~Column();
    };

    private:
        int *matrix;
        std::size_t rows;
        std::size_t cols;
        std::vector <Column> ptr_to_clos;
    public:
        explicit Matrix(size_t rows_, size_t cols_);

        ~Matrix();

        int getRows() const;
        int getColumns() const;

        const Column& operator [] (const int index) const;
        Column& operator [] (int index);
        bool operator == (const Matrix& m) const;
        bool operator != (const Matrix& m) const;
        Matrix& operator *= (const int num);
};

#endif