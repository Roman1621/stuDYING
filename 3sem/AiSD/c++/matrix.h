#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

template <typename T>
class Matrix{
    public:
        Matrix();
        Matrix(int number, int size);
        void fill(std::vector<T>& arr);

        bool operator< (const Matrix<T>& oper) const;
        bool operator<= (const Matrix<T>& oper) const;
        bool operator> (const Matrix<T>& oper) const;
        bool operator>= (const Matrix<T>& oper) const;
        bool operator== (const Matrix<T>& oper) const;
        int operator~ () const;

        int get_number() const;
        int get_size() const;
        T get_element(int i, int j) const;
        T get_trace() const;

    private:
        int size, number;
        std::vector<T> data;
};

#endif