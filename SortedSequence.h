#ifndef SORTEDSEQUENCE_H
#define SORTEDSEQUENCE_H


#include "ArraySequence.h"



template<class T>
bool cmp_default(const T& t1, const T& t2) {return t1 < t2;}

template<class T>
class SortedSequence : private ArraySequence<T> {
private:
    bool(*cmp)(const T& t1, const T& t2) = cmp_default;
public:

    SortedSequence() : ArraySequence<T>(){};


    int get_len(){
        return this->ArraySequence<T>::get_len();
    };

    T get_first(){
        return this->ArraySequence<T>::get_first();
    };

    T get_last(){
        return this->ArraySequence<T>::get_last();
    };

    T get_i(int index){
        return this->ArraySequence<T>::get_i(index);
    };

    T &operator[](int index){
        return this->ArraySequence<T>::operator[](index);
    };

    void add(T element){
        if (get_len() == 0){
            this->ArraySequence<T>::append(element);
            return;
        }

        this->ArraySequence<T>::append(element);
        int left = 0;
        int right = get_len() - 1;

        while (left < right){
            int mid = (right + left) / 2;
            if (cmp(element, operator[](mid)))
                right = mid;
            else
                left = mid + 1;
        }

        for (int j = get_len() - 1; j > left; j--){
            operator[](j) = operator[](j - 1);
        }
        operator[](left) = element;
    };

    void removeLast(){
        this->ArraySequence<T>::pop(get_len() - 1);
    };


    void remove(int index){
        this->ArraySequence<T>::pop(index);
    };

    void removeCount(int count) {
        for (int i = get_len() - 1; i >= get_len() - count; i--)
            removeLast();
    };
};



template<class T>
std::ostream& operator<< (std::ostream &out, SortedSequence<T> &arr){
    for (int i = 0; i < arr.get_len(); i++){
        std::cout << arr[i] << " ";
    }
    return std::cout;
}


#endif // SORTEDSEQUENCE_H
