#ifndef PROSTO_SEQUENCE_H
#define PROSTO_SEQUENCE_H
#include <iostream>
#include <string>
#include <functional>


template <class T>
class Sequence {
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    virtual T get_first() = 0;

    virtual T get_last() = 0;

    virtual T get_i(int index) = 0;

    virtual T& operator[](int index) = 0;

    virtual int get_len() = 0;

    virtual void set_i(int index, T item) = 0;

    virtual int where(T item) = 0;

    virtual void append(T item) = 0;

    virtual void prepend(T item) = 0;

    virtual void insert(T item, int index) = 0;

    virtual Sequence<T> *getSubSequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T> *clone() = 0;

    virtual  Sequence<T> *empty() = 0;

    //virtual Sequence<T> *concat(Sequence<T> *sequence) = 0;

//    virtual Sequence<T> *split(int index) = 0;

   // virtual Sequence<T>* zip(Sequence<T> sequence1, Sequence<T> sequence2) = 0;
};

#endif //PROSTO_SEQUENCE_H