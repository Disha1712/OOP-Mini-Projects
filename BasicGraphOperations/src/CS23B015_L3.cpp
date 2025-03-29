#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
class Graph{
    private:
        int n,m;
        map<int,set<int>> adj;
    public:
        Graph(): n(0),m(0){}
        Graph(int n,int m,map<int,set<int>> adj): n(n),m(m),adj(adj){}
        void operator +(Graph b){
            n=max(this->n,b.n);
            for (auto [vertex,neigh]:b.adj){
                for (auto v:neigh){
                    adj[vertex].insert(v);
                    adj[v].insert(vertex);
                }
            }
            int e=0;
            for (auto [vertex,neigh]:adj){
                e+=neigh.size();
            }
            m=e/2;
        }
        void operator -(Graph b){
            n=max(this->n,b.n);
            map<int,set<int>> ad;
            int e=0;
            for (auto [vertex,neigh]:adj){
                for (auto v:neigh){
                    if (b.adj.count(vertex) && b.adj[vertex].find(v)!=b.adj[vertex].end()){
                        ad[vertex].insert(v);   
                        ad[v].insert(vertex);
                        e++;
                    }
                }
            }
            adj=ad;
            m=e/2;
        }
        void operator !(){
            int e=n*(n-1)/2-m;
            map<int,set<int>> ad;
            for (int i=0;i<n;i++){
                for (int j=i+1;j<n;j++){
                    if ((!adj.count(i) || !adj[i].count(j))){
                        ad[i].insert(j);
                        ad[j].insert(i);
                    }
                }
            }
            adj=ad;
            m=e;
        }
        
        void add_edge(int u,int v){
            adj[u].insert(v);
            adj[v].insert(u);
        }
        void remove_edge(int u,int v){
            if (adj[u].find(v)!=adj[u].end()){
                adj[u].erase(v);
            }
            if (adj[v].find(u)!=adj[v].end()){
                adj[v].erase(u);
            }
        }
        bool dfs(int u,int v,vector<bool>& visited){
            if (adj.find(u)==adj.end()) return false;
            if (adj[u].find(v)!=adj[u].end()) return true;
            visited[u]=true;
            for (auto i:adj[u]){
                if (!visited[i] && dfs(i,v,visited)){
                    return true;
                }
            }
            return false;
        }
        bool isReachable(int u,int v){
            if (u<0 || v<0 || u>=n || v>=n) return false;
            if (u==v)   return true;
            vector<bool> visited(n,0);
            return dfs(u,v,visited);
        }
        friend ostream& operator <<(ostream& stream, Graph& graph);
        friend istream& operator >>(istream& stream,Graph& graph);
};
ostream& operator <<(ostream& stream,Graph& graph){
    for (int vertex=0;vertex<graph.n;vertex++){
        stream<<"Vertex "<<vertex<<": ";
        for (auto n:graph.adj[vertex]){
            stream<<n<<" ";
        }
        stream<<endl;
    }
    return (stream);
}
istream& operator >>(istream& stream,Graph &graph){
    string g;
    stream>>g;
    stream>>graph.n>>graph.m;
    for (int i=0;i<graph.m;i++){
        int u,v;
        stream>>u>>v;
        graph.add_edge(u,v);
    }
    return stream;
}
int main(){
    Graph g;
    cin>>g;
    while (1){
        string input;
        cin>>input;
        if (input=="union"){
            Graph h;
            cin>>h;
            g+h;
        }
        else if (input=="intersection"){
            Graph h;
            cin>>h;
            g-h;
        }
        else if (input=="complement"){
            !g;
        }
        else if (input=="isReachable"){
            int u,v;
            cin>>u>>v;
            if (g.isReachable(u,v)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
        else if (input=="add_edge"){
            int u,v;
            cin>>u>>v;
            g.add_edge(u,v);
        }
        else if (input=="remove_edge"){
            int u,v;
            cin>>u>>v;
            g.remove_edge(u,v);
        }
        else if (input=="printGraph"){
            cout<<g;
        }
        else break;
    }
}