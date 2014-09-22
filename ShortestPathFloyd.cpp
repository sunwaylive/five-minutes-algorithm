#include <iostream>
using namespace std;

const int VN = 5;
const int MAXVALUE = 100000;
class Graph{
public:
    Graph();
    void addEdge(int s, int e, int weight);
    void floyd(int n);
    int edge[VN][VN];
    int dist[VN][VN];
    int path[VN][VN];
};

Graph::Graph(){
    for(int i = 0; i < VN; ++i){
        for(int j = 0; j < VN; ++j){
            if(i == j) edge[i][j] = 0;
            else edge[i][j] = MAXVALUE;
        }
    }
}

void Graph::addEdge(int s, int e, int weight){
    edge[s][e] = weight;
}

//1. initialize  2.iterative mid vertex
void Graph::floyd(int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            dist[i][j] = edge[i][j];
            if(i != j && dist[i][j] < MAXVALUE){
                path[i][j] = i;
            }else{
                path[i][j] = -1;
            }
        }
    }

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][k] < MAXVALUE && dist[k][j] < MAXVALUE
                   &&dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

int main()
{
    Graph g;
    g.addEdge(0, 1, 30);
    g.addEdge(0, 3, 10);
    g.addEdge(0, 4, 50);
    g.addEdge(1, 2, 60);
    g.addEdge(1, 4, 80);
    g.addEdge(3, 4, 30);
    g.addEdge(4, 2, 40);
    g.addEdge(4, 0, 50);

    int start, end;
    cin>>start>>end;
    g.floyd(VN);
    cout<<g.dist[start][end] <<endl;
    int p = g.path[start][end];
    while(p != -1){
        cout<<p<<" ";
        p = g.path[start][p];
    }
    return 0;
}
