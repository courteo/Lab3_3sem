#include "iostream"
#include "graph.h"
#include "complex"
#include "string"
#ifndef DAR_H_INTERFACE_H
#define DAR_H_INTERFACE_H

template<class T>
bool cmp(T a1, T a2) {
    return a1 < a2;
}

void testFunc(int Type);

void Delete(int Type, ArraySequence<Graph<int>> *ArrInt,
            ArraySequence<Graph<double>> *ArrDouble);
template<class T>
void DeleteType(ArraySequence<Graph<T>> *ArrInt);



void DeleteAll(int Type, ArraySequence<Graph<int>> *ArrInt,
                  ArraySequence<Graph<double>> *ArrDouble);
template<class T>
void DeleteAllType(ArraySequence<Graph<T>> *ArrInt);



void readGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
               ArraySequence<Graph<double>> *ArrDouble);
template<class T>
Graph<T> readGraphType(int count);


void printAll(int Type, ArraySequence<Graph<int>> *ArrInt,
                        ArraySequence<Graph<double>> *ArrDouble);
void printArray(int Type, ArraySequence<Graph<int>> *ArrInt,
                          ArraySequence<Graph<double>> *ArrDouble, int index1);


void AddVertexToGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
                                ArraySequence<Graph<double>> *ArrDouble);
template<class T>
void AddVertexToGraphType(int index, ArraySequence<Graph<T>> *Arr);



void DeleteVertexToGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
                      ArraySequence<Graph<double>> *ArrDouble);
template<class T>
void DeleteVertexToGraphType(int index, ArraySequence<Graph<T>> *Arr);



void GetPathBetween2Vertexes(int Type, ArraySequence<Graph<int>> *ArrInt,
                      ArraySequence<Graph<double>> *ArrDouble);
template<class T>
void GetPathBetween2VertexesType(int index, ArraySequence<Graph<T>> *Arr);


int get_type();



int get_int() {
    int a;
    std::cin >> a;
    return a;
}

int get_int(int up) {
    int a;
    std::cin >> a;
    if (a > up) {
        std::cout << "Can you enter again\n";
        return get_int(up);
    }
    return a;
}

int get_int(int down, int up) {
    int a;
    std::cin >> a;

    if (a > up || a < down) {
        std::cout << "Can you enter again\n";
        return get_int(down, up);
    }
    return a;
}

double get_double() {
    double a;
    std::cin >> a;
    return a;
}


int get_type() {
    std::cout << "Enter number to operate with certain data type: \n"
              << "\t1 - int\n"
              << "\t2 - double\n"
              << "\t0 - exit\n";
    return get_int(0, 2);
}

void interface(ArraySequence<Graph<int>> &ArrInt,
                       ArraySequence<Graph<double>> &ArrDouble){

    while (true) {
        std::cout << "Can you choose option:\n"
                  << "\t0 - exit\n"
                  << "\t1 - Enter Graph\n"
                  << "\t2 - print all Graphs\n"
                  << "\t3 - print Graph[i]\n"
                  << "\t4 - tests\n"
                  << "\t5 - delete all\n"
                  << "\t6 - delete Graph[i]\n"
                  << "\t7 - Add Vertex to Graph[i]\n"
                  << "\t8 - Delete Vertex to Graph[i]\n"
                  << "\t9 - Get path between 2 Vertexes in Graph[i]\n";
        int item0 = get_int(0, 9);
        //std::cout << "qqewqw   " << item0 << std::endl;
        if (item0 == 0) {
            std::cout << "Thanks for being with us ^-^\n";
            break;
        }
        int Type = get_type();
        switch (item0) {
            case 1:
                readGraph(Type, &ArrInt, &ArrDouble);
                break;
            case 2:
                printAll(Type, &ArrInt, &ArrDouble);
                break;
            case 3:
                printArray(Type, &ArrInt, &ArrDouble, -1);
                break;
            case 4:
                testFunc(Type);
                break;
            case 5:
                DeleteAll(Type, &ArrInt, &ArrDouble);
                break;
            case 6:
                Delete(Type, &ArrInt, &ArrDouble);
                break;
            case 7:
                AddVertexToGraph(Type, &ArrInt, &ArrDouble);
                break;
            case 8:
                DeleteVertexToGraph(Type, &ArrInt, &ArrDouble);
                break;
            case 9:
                GetPathBetween2Vertexes(Type, &ArrInt, &ArrDouble);
                break;

        }
    }


}



void readGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
               ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    std::cout << "Enter count of elements or 0 to exit, please: \n";
    int count;
    std::cin >> count;
    while (count <= 0) {
        if (count < 0)
            std::cout << "count can not be less than 0, please ReEnter count\n";
        if (count == 0)
            return;
        std::cin >> count;

    }

    Graph<int> ArrInt1;
    Graph<double> ArrDouble1;
    switch (Type) {
        case 1:
            ArrInt->append(readGraphType<int>(count));
            break;
        case 2:
            ArrDouble1 = readGraphType<double>(count);
            ArrDouble->append(ArrDouble1);
            break;
        default:
            break;
    }
}

template<class T>
Graph<T> readGraphType(int count){
    std::cout << "Can you enter the elements, please:\n";

    ArraySequence<ArraySequence<T>> item1 = ArraySequence<ArraySequence<T>>(count);
    for (int j = 0; j < count; j++) {
        item1.append(ArraySequence<T>(count));

        for (int i = 0; i < count; i++){
            T item;
            std::cin >> item;

            item1[j].append(item);
        }
    }
    Graph<T> arr(item1);
    return arr;
}



void printArray(int Type, ArraySequence<Graph<int>> *ArrInt,
                     ArraySequence<Graph<double>> *ArrDouble, int index1){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    if (index1 < 0 ){

        int length;
        if (Type = 1){
            length = ArrInt->get_len();

            if (length == 0){
                std::cout << "Sorry, but Length == 0\n";
                return;
            }

            std::cout << "Can you choose index of massive from 0 to " << ArrInt->get_len() - 1 << ",please\n";
        }
        else{
            length = ArrDouble->get_len();
            if (length == 0){
                std::cout << "Sorry, but Length == 0 \n";
                return;
            }
            std::cout << "Can you choose index of massive from 0 to " << ArrDouble->get_len() - 1 << ",please\n";
        }


        int index;
        std::cin >> index;
        while (index < 0 || index >= length) {
            if (index < 0 || index >= length)
                std::cout << "index can not be less than 0 and be bigger than length, please ReEnter count or enter -1 to exit\n";
            std::cin >> index;
            if (index == -1)
                return;

        }

        if (Type == 1)
            std::cout << ArrInt->operator[](index);
        else
            std::cout << ArrDouble->operator[](index);
    }
    else {
        if (Type == 1)
            std::cout << ArrInt->operator[](index1);
        else
            std::cout << ArrDouble->operator[](index1);
    }

}

void printAll(int Type, ArraySequence<Graph<int>> *ArrInt,
                        ArraySequence<Graph<double>> *ArrDouble) {

    if (Type == 0) {
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    if (Type == 1) {
        if (ArrInt->get_len() == 0){
            std::cout << "Sorry, but Length == 0 \n";
            return;
        }
        for (int i = 0; i < ArrInt->get_len(); i++) {
            printArray(Type, ArrInt, ArrDouble, i);
            std::cout << "\n";
        }
    } else {
        if (ArrDouble->get_len() == 0){
            std::cout << "Sorry, but Length == 0 \n";
            return;
        }
        for (int i = 0; i < ArrDouble->get_len(); i++) {
            printArray(Type, ArrInt, ArrDouble, i);
            std::cout << "\n";
        }

    }
}



void Delete(int Type, ArraySequence<Graph<int>> *ArrInt,
                      ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }
    switch (Type) {
        case 1:
            DeleteType<int>(ArrInt);
            break;
        case 2:
            DeleteType<double>(ArrDouble);
            break;

    }

}

template<class T>
void DeleteType(ArraySequence<Graph<T>> *ArrInt){
    if (ArrInt->get_len() == 0){
        std::cout << "Sorry, but massive is empty \n";
        return;
    }

    while (true){

        int length = ArrInt->get_len();
        if (ArrInt->get_len() == 0){
            std::cout << "Sorry, but massive is empty \n";
            return;
        }

        std::cout << "You have " << length << " massives\n"
                  << "\t0 - to exit\n"
                  << "\t1 - delete Sequence[i]\n";

        int index1 = get_int(0, 2);
        if (index1 == 0)
            return;

        std::cout << "Can you choose index of massive from 0 to " << ArrInt->get_len() - 1 << ",please\n";


        int index;
        std::cin >> index;
        while (index < 0 || index >= length) {

            if (index < 0 || index >= length)
                std::cout << "index can not be less than 0 and be bigger than length, please ReEnter count or enter -1 to exit\n";
            std::cin >> index;
            if (index == -1)
                return;
        }
        ArrInt->pop(index);
    }
}

void DeleteAll(int Type, ArraySequence<Graph<int>> *ArrInt,
               ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    switch (Type) {
        case 1:
            DeleteAllType<int>(ArrInt);
            break;
        case 2:
            DeleteAllType<double>(ArrDouble);
            break;

    }
}

template<class T>
void DeleteAllType(ArraySequence<Graph<T>> *ArrInt){
    if (ArrInt->get_len() == 0){
        std::cout << "Sorry, but massive is empty \n";
        return;
    }
    int length =ArrInt->get_len();
    for (int i = 0; i < length; i++){
        ArrInt->pop(0);
    }
}




void AddVertexToGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
                      ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    std::cout << "Enter index of elements or -1 to exit, please: \n";
    int index;
    std::cin >> index;
    while (index < 0) {
        if (index < 0)
            std::cout << "count can not be less than 0, please ReEnter count\n";
        std::cin >> index;
        if (index == -1)
            return;
    }


    switch (Type) {
        case 1:
           AddVertexToGraphType<int>(index, ArrInt);
            break;
        case 2:
            AddVertexToGraphType<double>(index, ArrDouble);
            break;
        default:
            break;
    }
}


template<class T>
void AddVertexToGraphType(int index, ArraySequence<Graph<T>> *Arr){
    std::cout << "Can you input weights of vertex\n";
    ArraySequence<T> weights;
    T weight;
    for (int i = 0; i < Arr->operator[](index).vertexCount(); i++){
        std::cin >> weight;
        weights.append(weight);
    }
    Arr->operator[](index).Add(weights);
}


void DeleteVertexToGraph(int Type, ArraySequence<Graph<int>> *ArrInt,
                      ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    std::cout << "Enter index of elements or -1 to exit, please: \n";
    int index;
    std::cin >> index;
    while (index < 0) {
        if (index < 0)
            std::cout << "count can not be less than 0, please ReEnter count\n";
        std::cin >> index;
        if (index == -1)
            return;
    }


    switch (Type) {
        case 1:
            DeleteVertexToGraphType<int>(index, ArrInt);
            break;
        case 2:
            DeleteVertexToGraphType<double>(index, ArrDouble);
            break;
        default:
            break;
    }
}


template<class T>
void DeleteVertexToGraphType(int index, ArraySequence<Graph<T>> *Arr){
    std::cout << "Can you input vertex\n";

    int vertex;
    std::cin >> vertex;
    while (vertex < 1 || vertex > Arr->operator[](index).vertexCount()){
        std::cout << "Sorry this vertex doesnt exist, Please, ReEnter vertex\n";
        std::cin >> vertex;
    }

    Arr->operator[](index).DeleteVertex(vertex);
}

void GetPathBetween2Vertexes(int Type, ArraySequence<Graph<int>> *ArrInt,
                         ArraySequence<Graph<double>> *ArrDouble){
    if (Type == 0){
        std::cout << "Thanks for being with us ^-^\n";
        return;
    }

    std::cout << "Enter index of elements or -1 to exit, please: \n";
    int index;
    std::cin >> index;
    while (index < 0) {
        if (index < 0)
            std::cout << "count can not be less than 0, please ReEnter count\n";
        std::cin >> index;
        if (index == -1)
            return;
    }


    switch (Type) {
        case 1:
            GetPathBetween2VertexesType<int>(index, ArrInt);
            break;
        case 2:
            GetPathBetween2VertexesType<double>(index, ArrDouble);
            break;
        default:
            break;
    }
}


template<class T>
void GetPathBetween2VertexesType(int index, ArraySequence<Graph<T>> *Arr){
    std::cout << "Can you input vertex\n";

    int vertexIn, vertexOut;
    std::cin >> vertexIn >> vertexOut;
    while (    (vertexIn < 0 || vertexIn >= Arr->operator[](index).vertexCount())
            && (vertexOut < 0 || vertexOut >= Arr->operator[](index).vertexCount()) ){
        std::cout << "Sorry this vertex doesnt exist, Please, ReEnter vertex\n";
        std::cin >> vertexIn >> vertexOut;
    }


    std::cout << Dijkstra(Arr->operator[](index), vertexIn, vertexOut);
}

void testFunc(int Type){

}

#endif //DAR_H_INTERFACE_H

