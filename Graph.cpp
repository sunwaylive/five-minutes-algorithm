#include <iostream>
#include <stack>
#include <queue>
using namespace std;

const int VN = 3;

class Graph{
public:
    Graph();
    void addEdge(int start, int end, int weight);
    void bfs();
    void dfs();
    void topoSort();
public:
    int edge[VN][VN];
    int inDegree[VN];
};

Graph::Graph(){
    for(int i = 0; i < VN; ++i){
        for(int j = 0; j < VN; ++j){
            edge[i][j] = INT_MAX;
        }
    }
    for(int i = 0; i < VN; ++i)
        inDegree[i] = 0;
}

void Graph::addEdge(int start, int end, int weight){
    edge[start][end] = weight;//if unordered, we should add symmetric edge
    inDegree[end]++;
}

void Graph::bfs(){
    bool *visited = new bool[VN];
    for(int i = 0; i < VN; ++i)
        visited[i] = false;

    queue<int> que;
    for(int i = 0; i < VN; ++i){
        if(!visited[i]){
            que.push(i);
            visited[i] = true;

            while(!que.empty()){
                int c = que.front();
                que.pop();
                cout<<c <<" ";

                for(int j = 0; j < VN; ++j){
                    if(edge[c][j] != INT_MAX && !visited[j]){
                        que.push(j);
                        visited[j] = true;
                    }
                }
            }
        }
    }
    delete visited;
}

void Graph::dfs(){
    bool *visited = new bool[VN];
    for(int i = 0; i < VN; ++i)
        visited[i] = false;

    stack<int> stk;
    for(int i = 0; i < VN; ++i){
        if(!visited[i]){
            stk.push(i);
            while(!stk.empty()){
                int c = stk.top();
                stk.pop();
                visited[c] = true;
                cout<<c <<" ";

                for(int j = 0; j < VN; ++j){
                    if(edge[c][j] != INT_MAX && !visited[j]){
                        stk.push(j);
                    }
                }
            }
        }
    }
    delete visited;
}

void Graph::topoSort(){
    bool *visited = new bool[VN];
    for(int i = 0; i < VN; ++i)
        visited[i] = false;

    queue<int> que;
    for(int i = 0; i < VN; ++i){
        if(!visited[i] && inDegree[i] == 0){
            que.push(i);

            while(!que.empty()){
                int c = que.front();//cur
                que.pop();
                cout<<c <<" ";
                visited[c] = true;
                for(int j = 0; j < VN; ++j){
                    if(!visited[j] && edge[c][j] != INT_MAX){
                        inDegree[j]--;
                    }
                    if(!visited[j] && inDegree[j] == 0) {
                        que.push(j);
                        visited[j] = true;
                    }
                }//end for
            }//end while
        }//end if
    }//end for
    delete visited;
}

int main(){
    Graph g;
    g.addEdge(0, 1, 0);
    g.addEdge(2, 1, 0);
    g.addEdge(0, 2, 0);
    //g.addEdge(1, 2, 0);
    g.bfs();
    cout<<endl;
    g.dfs();
    cout<<endl;
    g.topoSort();
    cout<<endl;
    return 0;
}
