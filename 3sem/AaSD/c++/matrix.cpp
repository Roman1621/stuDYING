#include "matrix.h"

template <typename T>
Matrix<T>::Matrix(){

}
        
template <typename T>
Matrix<T>::Matrix(int number, int size):number(number), size(size){
    data.resize(size*size);
}

template <typename T>
void Matrix<T>::fill(std::vector<T>& arr){
    for(int i = 0; i < size; i++)
        data[i] = arr[i];
}

template <typename T>        
bool Matrix<T>::operator< (const Matrix<T>& oper) const{
    return get_trace() < oper.get_trace();
}

template <typename T>
bool Matrix<T>::operator<= (const Matrix<T>& oper) const{
    return get_trace() <= oper.get_trace();
}

template <typename T>
bool Matrix<T>::operator> (const Matrix<T>& oper) const{
    return get_trace() > oper.get_trace();
}

template <typename T>
bool Matrix<T>::operator>= (const Matrix<T>& oper) const{
    return get_trace() >= oper.get_trace();
}

template <typename T>
bool Matrix<T>::operator== (const Matrix<T>& oper) const{
    return get_trace() == oper.get_trace();
}

template <typename T>
int Matrix<T>::operator~ () const{
    return get_number();
}

template <typename T>
int Matrix<T>::get_number() const{
    return number;
}

template <typename T>
int Matrix<T>::get_size() const{
    return size;
}

template <typename T>
T Matrix<T>::get_element(int i, int j) const{
    if(i >= size || j >= size) throw "Element index is out of range";
    return data[i*size+j];
}

template <typename T>
T Matrix<T>::get_trace() const{
    T sum = get_element(0, 0);
    for(int i = 1; i < size; i++) sum += get_element(i, i);
    return sum;
}