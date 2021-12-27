
#ifndef PROSTO_LinkedSequence_H
#define PROSTO_LinkedSequence_H
#include "link_list.h"
#include "sequence.h"
#include "iostream"


template<class T>
class LinkedSequence: public Sequence<T> {
private:
    Linked_List<T> Llst;
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    LinkedSequence<T>& operator = (const LinkedSequence<T> &listSequence) {
        Llst = listSequence.Llst;
        return *this;
    }

    LinkedSequence<T>& operator = (LinkedSequence<T> *listSequence) {
        Llst = listSequence->Llst;
        return *this;
    }

    T &operator[](int index) {
        if (index < 0 || index >= get_len())
            throw IndexOutOfRange(get_len(), index);
        return Llst[index];
    }

    int get_len(){
        return Llst.get_len();
    }

    LinkedSequence(){
        Llst = Linked_List<T>();
    }

    explicit LinkedSequence(int size){
        Llst = Linked_List<T>(size);
    }

    explicit LinkedSequence(int count, T* items){
        Llst = Linked_List<T>(count, items);
    }

    LinkedSequence(const LinkedSequence<T> &list){
        Llst = list.Llst;
    }

    explicit LinkedSequence(Sequence<T> &sequence){
        for (int i = 0; i < sequence.get_len(); i++) {
            append(sequence[i]);
        }
    }

    explicit LinkedSequence(const Linked_List<T> &list){
        Llst = list;
    }

    T get_first(){
        if (Llst.get_len() == 0) throw IndexOutOfRange(get_len(), get_len());
        return Llst.get_first();
    }

    T get_last(){
        if (Llst.get_len() == 0) throw IndexOutOfRange(get_len(),get_len());
        return Llst.get_last();
    }

    T get_i(int index){
        if (index < 0 || index >= Llst.get_len()) throw IndexOutOfRange(get_len(), index);
        return Llst.get_i(index);
    }

    void set_i(int index, T item){
        if (index < 0 || index >= Llst.get_len()) throw IndexOutOfRange(get_len(), index);
        Llst.set_i(index, item);
    }

    LinkedSequence<T> *getSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= Llst.get_len())
            throw IndexOutOfRange(get_len(), startIndex);
        if (endIndex < 0 || endIndex > Llst.get_len())
            throw IndexOutOfRange(get_len(), endIndex);

        int delta = startIndex < endIndex ? 1 : -1;

        auto NewLst = new LinkedSequence<T>;
        for (int i = startIndex; i != endIndex; i += delta) {
            NewLst->append(Llst.get_i(i));
        }

        return NewLst;
    }

    LinkedSequence<T>* clone(){
        return new LinkedSequence<T>(*this);
    }

    LinkedSequence<T>* empty(){
        return new LinkedSequence<T>();
    }
    void append(T item){
        Llst.append(item);
    }

    void prepend(T item){
        Llst.prepend(item);
    }

    void insert(T item, int index){
        this->Llst.insert(item, index);
    }

    LinkedSequence<T> *concat(LinkedSequence<T> *list){
        for ( int i = 0; i < list->get_len(); i++){
            this->append(list->get_i(i));
        }
        return this;
    }

    int where(T item){
        for (int i = 0; i < this->Llst.get_len(); i++){
            //if (this->Llst.get_i(i) == item)
                return i;

        }
        return -1;
    }

    LinkedSequence<LinkedSequence<T>*> *split(int index) {
        if (index < 0 || index >= get_len())
            throw IndexOutOfRange();

        auto *t1 = new LinkedSequence<T>;
        auto *t2 = new LinkedSequence<T>;
        auto *NewArr = new LinkedSequence<LinkedSequence<T>*>;

        for (int i = 0; i < index; i++){
            t1->append(this->Llst.get_i(i));
        }

        for (int i = index; i < this->Llst.get_len(); i++){
            t2->append(this->Llst.get_i(i));
        }
        NewArr->append(t1);
        NewArr->append(t2);
        return NewArr;
    }

    LinkedSequence<Linked_List<T>*>* zip(LinkedSequence<T> lst){
        auto *NewLst = new LinkedSequence<Linked_List<T>*>;
        int min;
        if (Llst.get_len() < lst.Llst.get_len()){
            min = Llst.get_len();
        }
        else {
            min = lst.Llst.get_len();
        }

        for (int i = 0; i < min; i++){
            auto *tuple = new Linked_List<T>(2);
            tuple->set_i(0, get_i(i));
            tuple->set_i(1, lst.get_i(i));
            NewLst->append(tuple);
        }

        return NewLst;
    }



    T pop(int index) {
        if (index < 0 || index >= Llst.get_len())
            throw IndexOutOfRange(Llst.get_len(), index);

        T item = Llst[index];
        for (int i = index; i < Llst.get_len() - 1; i++) {
            set_i(i, Llst.get_i(i+1));
        }

        Llst.DeleteLast();
//        Llst.get_i(Llst.get_len() - 2);
        return item;
    }

    bool operator == (LinkedSequence<T>& arr1){
        if (get_len() != arr1.get_len())
            return false;

        for (int i = 0; i < arr1.get_len(); i++){
            if (arr1[i] != operator[](i)){
                return false;
            }
        }
        return true;
    }

};

template<class T>
std::ostream & operator << (std::ostream &out, LinkedSequence<T> link){
    for (int i = 0; i < link.get_len(); i++){
        std::cout << link[i] << " ";
    }
    return std::cout << std::endl;
}
#endif //PROSTO_LinkedSequence_H
