#ifndef __MATRIX__
#define __MATRIX__

class Matrix {
    class Array1 {
        private: 
            int*  pRow;
            int cols;
        public:
            friend class Matrix;
            const int& operator[](int i) const;
            int& operator[] (int i);
            Array1();
            ~Array1();
    };

    private:
        Array1 *matrix;
        int rows;
        int cols;

    public:
        explicit Matrix(int rows_, int cols_);

        ~Matrix();

        int getRows() const;
        int getColumns() const;

        const Array1& operator [] (const int index) const;
        Array1& operator [] (int index);
        bool operator == (const Matrix& m) const;
        bool operator != (const Matrix& m) const;
        Matrix& operator *= (const int num);
};

#endif