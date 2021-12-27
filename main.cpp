#include <iostream>
#include "graph.h"
#include "interface.h"
int main() {
    //ArraySequence<int> a(10);
    //a.append(1);
    //a.append(2);
    //a.pop(1);
    //std::cout << a;
//    Geraph<int> a;
//    a.InputGraph();
//    std::cout << "qwe \n";
    //0 7 9 0 0 14
    //7 0 10 15 0 0
    //9 10 0 11 0 2
    //0 15 11 0 6 0
    //0 0 0 6 0 9
    //14 0 2 0 9 0
    // a.PrintGraph();
    //a.Add();
    //a.PrintGraph();
    //a.DeleteVertex(7);
//    std::cout << Dijkstra(a, 1, 2) << '\n';
ArraySequence<Graph<int>> ArrInt;
ArraySequence<Graph<double>> ArrDouble;


        interface(ArrInt, ArrDouble);


    //a.Colourize();
    return 0;
}
