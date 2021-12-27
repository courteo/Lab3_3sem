//
// Created by aitao on 25.03.2021.
//

#ifndef PROSTO_element_H
#define PROSTO_element_H
#include "iostream"

template <class T>
class Linked_List
{
private:

    struct element
    {
        T el;
        element* p_next;
        element GetPnext(){
            return  p_next;
        }
    };
    int len;
    element* head;
    element* end;
    void set_len(int len)
    {
        this->len=len;
    }
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    int get_len()
    {
        return len;
    }

    Linked_List<T>& operator = (const Linked_List<T> &linkedList) {
        Delete();
        for (element *elem = linkedList.head; elem; append(elem->el), elem = elem->p_next);

        return *this;
    }

    void DeleteLast(){
        element *el = head;
        while (el->p_next != end)
            el = el->p_next;
        el->p_next = nullptr;
        end = el;
        len -= 1;
    }


    Linked_List<T>& operator = (Linked_List<T> *linkedList) {
        Delete();
        for (element *elem = linkedList->head; elem; append(elem->el), elem = elem->p_next);

        return *this;
    }

    T &operator [] (int index) {
        if (index < 0 || index >= len) throw IndexOutOfRange(len, index);  //исключение выхода за массив

        element *el = head;
        for (int i = 0; i < index; i++) {
            el = el->p_next;
        }
        return el->el;
    }

    Linked_List ()
    {
        head = nullptr;
        end = nullptr;
        set_len(0);
    }

    Linked_List (int size)
    {
        if (size < 0) throw IndexOutOfRange(get_len(), size);
        if (size == 0) {
            head = nullptr;
            end = nullptr;
            set_len(0);
            return;
        }
        element* t1 = nullptr;
        element* t2 = nullptr;
        this->head = new element;
        this->end = new element;
        this->set_len(size);
        //this->head->el;
        this->head->p_next = nullptr;
        t2 = this->head;
        for(int i=1;i<size;i++)
        {
            t1 = new element;
            t1->el;
            t1->p_next = nullptr;
            t2->p_next = t1;
            t2 = t1;
            t1 = nullptr;
        }
        this->end = t2;
    }

//    Linked_List ()

    Linked_List (const Linked_List <T>& other)
    {
        int size = other.get_len();
        element* t1 = nullptr;
        element* t2 = nullptr;

        this->set_len(size);
        this->head = new element;
        this->head->el = other.get_i(0);
        this->head->p_next = nullptr;

        t2 = this->head;
        for(int i=1;i<size;i++)
        {
            t1 = new element;
            t1->el = other.get_i(i);
            t1->p_next = nullptr;
            t2->p_next = t1;
            t2 = t1;
            t1 = nullptr;
        }
        this->end = t2;
    }

    Linked_List (int count, T* items){
        element* t1 = nullptr;
        element* t2 = nullptr;
        this->head = new element;
        this->end = new element;
        this->set_len(count);
        this->head->el = items[0];
        this->head->p_next = nullptr;
        t2 = this->head;
        for(int i = 1;i < count;i++)
        {
            t1 = new element;
            t1->el = items[i];
            t1->p_next = nullptr;
            t2->p_next = t1;
            t2 = t1;
            t1 = nullptr;
        }
        this->end = t2;

    }

    ~Linked_List()
    {
        element* t1 = this->head;
        while(t1 != nullptr)
        {
            element* next = t1->p_next;
            delete t1;
            t1 = next;
        }
    }

    void Delete() {
        element *next = head;
        while (next != nullptr) {
            head = next;
            next = head->p_next;
            delete head;
        }
        head = nullptr;
        end = nullptr;
    }

    T get_first()
    {
        return this->head->el;
    }

    T get_last()
    {
        return this->end->el;
    }

    T get_i(int index) {
        return operator[](index);
    }

    void set_i(int index, T el) {
        if(index < this->get_len())
        {
            element* t1 = this->head;
            for (int i = 0; i < index; i++) {
                t1 = t1->p_next;
            }
            t1->el = el;
        }
        else
            throw IndexOutOfRange(get_len(), index);
    }

    void append(T item) {
        int nlen = get_len() + 1;
        set_len(nlen);
        element* t1 = new element;
        t1->el = item;
        t1->p_next = nullptr;
        if (end == nullptr) {
            head = t1;
            end = t1;
            return;
        }
        end->p_next = t1;
        end = t1;
    }

    void prepend( T item) {
        int nlen = get_len() + 1;
        set_len(nlen);
        element* t1 = new element;
        t1->el = item;
        if (head == nullptr) {
            t1->p_next = nullptr;
            head = t1;
            end = t1;
            return;
        }
        t1->p_next = this->head;
        head = t1;

    }

    void insert(T item, int index){
        if (index < 0 || index >= get_len()) throw IndexOutOfRange(get_len(), index);

        if (index == 0) {
            prepend(item);
            return;
        }
        if (index == get_len() - 1) {
            append(item);
            return;
        }

        element *el = head;

        for (int i = 0; i < index - 1; i++, el = el->p_next);

        auto *elNew = new element;
        elNew->p_next = el->p_next;
        elNew->el = item;
        el->p_next = elNew;
        set_len(get_len() + 1);
    }

    Linked_List<T> *concat(Linked_List<T> *list){
        for ( int i = 0; i < list->get_len(); i++){
            this->append(list->get_i(i));
        }
    }
};


#endif //PROSTO_element_H
