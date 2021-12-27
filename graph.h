#ifndef LAB3_3SEM_GRAPH_H
#define LAB3_3SEM_GRAPH_H
#include "linkseq.h"
#include "arraysequence.h"
#include "SortedSequence.h"

template<class T>
class Path {
    struct Vertex {
        int v1;
        int v2;
        T weight;
    };

    ArraySequence<Vertex> vertex;
public:
    struct Empty {};

    Path() = default;

    void addVertex(int v1, int v2, T weight) {
        vertex.append({v1, v2, weight});
    }

    T length() const {
        if (vertex.get_len() == 0)
            throw Empty();

        T res = vertex[0].weight;

        for (int i = 1; i < vertex; i++) {
            res += vertex[i].weight;
        }

        return res;
    }

    ArraySequence<int> getVertexes() {
        ArraySequence<int> res;
        if (vertex.get_len() == 0)
            return res;
        res.append(vertex[0].v1);
        for (int i = 0; i < vertex.get_len(); i++) {
            res.append(vertex[i].v2);
        }
        return res;
    }

    friend Path operator + (const Path<T>& p1, const Path<T>& p2) {
        Path<T> res;

        if (p1.vertex.get_last().v2 != p2.vertex.get_first().v1)
            return res;

        for (int i = 0; i < p1.vertex.get_len(); i++)
            res.vertex.append(p1.vertex.get_i(i));

        for (int i = 0; i < p2.vertex.get_len(); i++)
            res.vertex.append(p2.vertex.get_i(i));

        return res;
    }

    friend std::ostream& operator << (std::ostream& cout, const Path<T>& p) {
        cout << '{';
        for (int i = 0; i < p.vertex.get_len(); i++) {
            cout << '{' << p.vertex[i].v1 << ", " << p.vertex[i].v2 << ", " << p.vertex[i].weight << "}, ";
        }
        return cout << "\b\b}";
    }
};


template<class T>
class Graph {
private:
    struct ElementV{
        int p_vertex;
        T p_Weight;


        ElementV():     p_Weight(T(0)), p_vertex(0){};
        explicit ElementV(T weight, int vertex):
                        p_Weight(weight), p_vertex(vertex){};

        friend std::ostream& operator<< (std::ostream &out, ElementV &arr) {
            return std::cout << "--Weight: " << arr.p_Weight << "; Vertex: " << arr.p_vertex <<  ";-- ";
        }
    };
    ArraySequence<int> p_DegreeOfVertexes;

    ArraySequence<ArraySequence<ElementV>> p_WeightMatrix;
public:
    Graph(){
        p_DegreeOfVertexes = ArraySequence<int>();
        p_WeightMatrix      = ArraySequence<ArraySequence<ElementV>>();
    }

    Graph(ArraySequence<ArraySequence<T>>& matrix){
        p_DegreeOfVertexes = ArraySequence<int>(matrix.get_len());
        for (int i = 0; i < matrix.get_len(); i++)
            p_DegreeOfVertexes.append(0);

        p_WeightMatrix = ArraySequence<ArraySequence<ElementV>>(matrix.get_len());
        for (int i = 0; i < matrix.get_len(); i++){
            p_WeightMatrix.append(ArraySequence<ElementV>(matrix.get_len()));
            for (int j = 0; j < matrix.get_len(); j++){
                if (matrix[i][j] > 0){
                    p_DegreeOfVertexes[i]++;
                    p_DegreeOfVertexes[j]++;
                    ElementV el(matrix[i][j], j + 1);
                    p_WeightMatrix[i].append(el);
                }
            }
        }
        for (int i = 0; i < p_DegreeOfVertexes.get_len(); i++)
            p_DegreeOfVertexes[i] /= 2;

    }

    void Add(ArraySequence<T> temp){
        for (int i = 0; i < p_DegreeOfVertexes.get_len(); i++){
            if (temp[i] > 0) {
                ElementV el(temp[i], p_DegreeOfVertexes.get_len() + 1);
                p_WeightMatrix[i].append(el);
            }

        }


        auto Tempp = ArraySequence<ElementV>(p_DegreeOfVertexes.get_len() + 1);
        p_WeightMatrix.append(Tempp);

        for (int i = 0; i < p_DegreeOfVertexes.get_len(); i++){
            if (p_WeightMatrix[i].get_last().p_vertex == p_DegreeOfVertexes.get_len() + 1){
                ElementV el(p_WeightMatrix[i].get_last().p_Weight, i + 1);
                p_WeightMatrix[p_WeightMatrix.get_len() - 1].append(el);
            }

        }

        p_DegreeOfVertexes.append(0);
        SetDegree();

    }


    void SetDegree(){
        for (int i = 0; i < p_DegreeOfVertexes.get_len(); i++)
            p_DegreeOfVertexes[i] = 0;

        //for (int i = 0; i < p_DegreeOfVertexes.get_len(); i++)
        //    std::cout << p_DegreeOfVertexes[i] << " ";
        //std::cout << '\n';

        for (int i = 0; i < p_WeightMatrix.get_len(); i++)
            for (int j = 0; j < p_WeightMatrix[i].get_len(); j++)
            {
                //std::cout << p_WeightMatrix[i][j].p_vertex - 1 << std::endl;
                p_DegreeOfVertexes[p_WeightMatrix[i][j].p_vertex - 1]++;

            }



    }

    void DeleteVertex(int vertex){
        std::cout << " qweqw " << vertex << std::endl;
        for (int i = 0; i < p_WeightMatrix.get_len(); i++)
            for (int j = 0; j < p_WeightMatrix[i].get_len(); j++){
                if (p_WeightMatrix[i][j].p_vertex == vertex){
                    p_WeightMatrix[i].pop(j);
                }
            }
        //std::cout << p_WeightMatrix[2].get_len() << " " << p_WeightMatrix.get_last().get_len() << std::endl;
        p_WeightMatrix.pop(vertex - 1);

        p_DegreeOfVertexes.pop(vertex - 1);


        for (int i = 0; i < p_WeightMatrix.get_len(); i++)
            for (int j = 0; j < p_WeightMatrix[i].get_len(); j++){

                if (p_WeightMatrix[i][j].p_vertex > vertex)
                    p_WeightMatrix[i][j].p_vertex -= 1;
            }

        SetDegree();

    }








    T getWeight(int vertex1, int vertex2) {
        for (int i =0; i < p_WeightMatrix[vertex1-1].get_len(); i++)
            if (p_WeightMatrix[vertex1-1][i].p_vertex == vertex2)
                return p_WeightMatrix[vertex1-1][i].p_Weight;
    }

    int vertexCount() {
        return p_DegreeOfVertexes.get_len();
    }

    ArraySequence<std::pair<int, T>> getNeighbours(int vertex) {
        ArraySequence<std::pair<int, T>> res;

        for (int i = 0; i < p_WeightMatrix[vertex-1].get_len(); i++) {
            res.append({p_WeightMatrix[vertex-1][i].p_vertex, p_WeightMatrix[vertex-1][i].p_Weight});
        }

        return res;
    }

    ArraySequence<ArraySequence<ElementV>> GetWeights(){
        return p_WeightMatrix;
    }

    ElementV GetEdge(int i, int j){
        return p_WeightMatrix[i][j];
    }
};

template<class T>
struct Element {
    int vertex;
    T weight;

    bool operator < (const Element& element) const {
        return weight < element.weight;
    }

    friend std::ostream& operator << (std::ostream& cout, const Element& element) {
        return cout << '{' << element.vertex << '}';
    }
};

template<class T>
Path<T> Dijkstra(Graph<T>& graph, int vertexIn, int vertexOut) {
    ArraySequence<int> visited;
    ArraySequence<int> path;

    for (int i = 0; i < graph.vertexCount() + 1; i++) {
        path.append(-1);
        visited.append(i);
    }

    SortedSequence<Element<T>> queue;
    queue.add({vertexIn, T()});

    while(queue.get_len() != 0) {
        Element<T> element = queue.get_i(0);
        queue.remove(0);

        int vertex = element.vertex;

        auto arr = graph.getNeighbours(vertex);

        for (int i = 0; i < arr.get_len(); i++) {
            if (visited[arr[i].first] == arr[i].first || path[arr[i].first] > path[vertex] + arr[i].second) {
                visited[arr[i].first] = vertex;
                int p = path[vertex] + arr[i].second;
                path[arr[i].first] = p;
                for (int j = 0; j < queue.get_len(); j++) {
                    if (queue[j].vertex == arr[i].first) {
                        queue.remove(j);
                        break;
                    }
                }
                queue.add({arr[i].first, p});
                continue;
            }
        }
    }
    if (path[vertexOut] == vertexOut)
        return Path<T>();

    ArraySequence<int> vertexes;
    int last_vertex = vertexOut;
    while(last_vertex != vertexIn) {
        vertexes.append(last_vertex);
        last_vertex = visited[last_vertex];
    }
    vertexes.append(vertexIn);

    Path<T> res;

    for (int i = vertexes.get_len() - 1; i > 0; i--) {
        res.addVertex(vertexes[i], vertexes[i-1], graph.getWeight(vertexes[i-1], vertexes[i]));
    }

    return res;
}

template<class T>
std::ostream& operator <<(std::ostream& out, Graph<T>& graph){
    for (int i = 0; i < graph.GetWeights().get_len(); i++) {
        for (int j = 0; j < graph.GetWeights()[i].get_len(); j++)
            std::cout << "{ " << graph.GetEdge(i,j).p_Weight << " " << graph.GetEdge(i,j).p_vertex << "} ";

        std::cout << std::endl;
    }
    return std::cout << std::endl;
}


/*
template<class T>
Graph<T> InputGraph(Graph<T>& graph, int length){

    graph.p_WeightMatrix = ArraySequence<ArraySequence<ElementV>>(length);

    graph.p_DegreeOfVertexes = ArraySequence<int>(length);
    for (int i = 0; i < length; i++)
        graph.p_DegreeOfVertexes.append(0);

    T vertex;
    for (int i = 0; i < length; i++) {
        graph.p_WeightMatrix.append(ArraySequence<ElementV>(length));
        for (int j = 0; j < length; j++) {
            std::cin >> vertex;

            if (vertex > 0){
                graph.p_DegreeOfVertexes[i]++;
                graph.p_DegreeOfVertexes[j]++;

                ElementV el(vertex, j + 1);
                graph.p_WeightMatrix[i].append(el);
            }
        }
    }


    for (int i = 0; i < length; i++)
        graph.p_DegreeOfVertexes[i] /= 2;
}
*/
#endif //LAB3_3SEM_GRAPH_H

/*
0 0 159 5 0 7
0 0 15 0 0 4
159 15 0 0 2 0
5 0 0 0 8 0
0 0 2 8 0 0
7 4 0 0 0 0
 */