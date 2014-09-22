#include <iostream>
using namespace std;

const int VN = 5;

class Graph{
public:
    Graph();
    void shortestPathDijkstra(int , int);
    int choose(int);
    void addEdge(int s, int e, float weight);
public:
    float edge[VN][VN];
    float dist[VN];
    int path[VN];
    int s[VN]; // choose set
};

Graph::Graph(){
    for(int i = 0; i < VN; ++i){
        for(int j = 0; j < VN; ++j){
            edge[i][j] = INT_MAX;
        }
    }
}

void Graph::addEdge(int s, int e, float weight){
    edge[s][e] = weight;
}

//1. initialize 2. add start 3. add loop (find min, add, update)
void Graph::shortestPathDijkstra(int n, int v){
    //1. initialize
    for(int i = 0; i < n; ++i){
        dist[i] = edge[v][i];
        s[i] = 0;// 1 mean added
        if(i != v && dist[i] < INT_MAX){
            path[i] = v;
        }else{
            path[i] = -1;
        }
    }
    //2. add start
    s[v] = 1;
    dist[v] = 0;//self to self distance is 0
    //3. add loop
    for(int i = 0; i < n - 1; ++i){//n - 1 vertex left except v
        float min_dist = INT_MAX;
        int u = v;
        for(int j = 0; j < n; ++j){
            if(s[j] == 0 && dist[j] < min_dist){
                u = j;
                min_dist = dist[j];
            }
        }
        s[u] = 1;//v-u is the shortest

        //4. update the rest
        for(int w = 0; w < n; ++w){
            if(s[w] == 0 && edge[u][w] < INT_MAX && dist[u] + edge[u][w] < dist[w]){
                dist[w] = dist[u] + edge[u][w];
                path[w] = u;
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
    g.shortestPathDijkstra(VN, start);
    cout<<g.dist[end]<<endl;
    while(end != start){
        cout<<end <<" ";
        end = g.path[end];
    }
    cout<<start <<endl;
    return 0;
}
