#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "iostream"

template<class T>
class Dynamic_array{
private:
    T* arr = nullptr;
    int len = 0;

    void set_len(int le)
    {
        this->len=le;
    }
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    int get_len() const {
        return this->len;
    }
    T &operator [] (int index) {
        if (index < 0 || index >= len) throw IndexOutOfRange(len, index);  //исключение выхода за массив

        return arr[index];
    }

    const T &operator [] (int index) const {
        if (index < 0 || index >= len) throw IndexOutOfRange(len, index);  //исключение выхода за массив

        return arr[index];
    }

    Dynamic_array<T> &operator = (const Dynamic_array<T> &dynamicArray) {
        resize(dynamicArray.len);
        for (int i = 0; i < dynamicArray.len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
        return *this;
    }

    Dynamic_array<T> &operator = (Dynamic_array<T> *dynamicArray) {
        this->resize(dynamicArray->get_len());
        for (int i = 0; i < get_len(); i++) {
            arr[i] = dynamicArray->arr[i];
        }
        return *this;
    }

    Dynamic_array(){
        T* t = nullptr;
        arr = t;
        set_len(0);
    }

    explicit Dynamic_array(int size){
        if (size < 0) throw IndexOutOfRange(get_len(), size);
        resize(size);

        set_len(size);
    }

    Dynamic_array(T* items, int size) {
        T* t = new T[size];
        arr = t;
        set_len(size);
        for (int i = 0; i< size; i++){
            arr[i] = items[i];
        }
    }

    Dynamic_array( Dynamic_array <T>& other)
    {
        int size = other.get_len();
        arr = new T[size];
        set_len(size);
        for (int i = 0; i< size; i++){
            arr[i] = other[i];
        }
    }

    ~Dynamic_array()
    {
        delete[] arr;
    }



    T get_i(int i) {
        if (get_len() <= i || i < 0)
            throw IndexOutOfRange(get_len(), i);
        return arr[i];
        //////////////////////
    }

    T get_first() {
        return *(arr);
    }

    T get_last()
    {
        return*(arr + get_len()-1);
    }

    void set_i(int i, T val){
        if (get_len() > i && i >= 0) {
            *(arr + i) = val;
        }
        else
            throw IndexOutOfRange(get_len(), i); ///////
    }

    void resize(int newSize){
       if (newSize < 0) throw IndexOutOfRange(get_len(), newSize);

       if (len == newSize) return;

        if (newSize == 0) {;
            set_len(0);
            delete[] arr;
            arr = nullptr;
        }

        T *t= new T[newSize];

        if (newSize <= get_len()){
            for (int i = 0; i < newSize; i ++) {
                *(t + i) = *(arr + i);
            }
        }
        else {
            for (int i = 0; i < this->get_len(); i ++) {
                *(t + i) = *(arr + i);
            }
            for (int i = this->get_len(); i < newSize; i ++) {
                //*(t + i) = T(0);
            }


        }
        set_len(newSize);
        if (arr != nullptr)
            delete[] arr;
        arr = t;
    }

    void delete_last(){
        if (get_len() <= 0) throw IndexOutOfRange(get_len(), get_len());

        T* t= new T[get_len() - 1];
        for (int i = 0; i < get_len() - 1; i ++) {
            *(t + i) = *(arr + i);
        }
        set_len(get_len() - 1);
        delete[] arr;
        arr = t;
    }

    void delete_first() {
        if (get_len()  <= 0) throw IndexOutOfRange(get_len(), get_len());

        T* t= new T[get_len() - 1];
        for (int i = 0; i < get_len() - 1; i ++) {
            *(t + i) = *(arr + i + 1);
        }
        set_len(get_len() - 1);
        delete[] arr;
        arr = t;
    }

    void remove_by_i(int i)  {
        if (i < 0 or i>= get_len()) throw IndexOutOfRange(get_len(), i);

        T* t= new T[get_len() - 1];
        if (i == 0 or i == get_len() - 1) {
            if (i == 0)
                delete_first();
            else
                delete_last();
        }
        else {
            for (int j = 0; j < i; j ++) {
                *(t + j) = *(arr + j + 1);
            }
            for (int j = i + 1; j < get_len(); j ++) {
                *(t + j) = *(arr + j + 1);
            }
        }
        set_len(get_len() - 1);
        delete[] arr;
        arr = t;
    }
};

#endif // DYNAMIC_ARRAY_H
