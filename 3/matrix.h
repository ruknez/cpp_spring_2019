#ifndef __MATRIX__
#define __MATRIX__

class Matrix {
    class Column {
        private: 
            int*  pRow = nullptr;
            size_t cols = 0;
        public:
            void SetParam (size_t cols_);
            const int& operator[](size_t i) const;
            int& operator[] (size_t i);
            int GetNumber (size_t num) const;
            void SetNumber (size_t num, int val);
            Column();
            ~Column();
    };

    private:
        Column *matrix;
        size_t rows;
        size_t cols;

    public:
        explicit Matrix(size_t rows_, size_t cols_);

        ~Matrix();

        size_t getRows() const;
        size_t getColumns() const;

        const Column& operator [] (const size_t index) const;
        Column& operator [] (size_t index);
        bool operator == (const Matrix& m) const;
        bool operator != (const Matrix& m) const;
        Matrix& operator *= (const int num);
};

#endif