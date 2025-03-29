#include <bits/stdc++.h>
using namespace std;
class Comparator{
    public:
        bool operator()(int a,int b){
            if (a>b) return 1;
            else return 0;
        }
};
class GraphAlgorithm{
    public:
    int v,e;
    vector<int> hype;
    map<int,vector<int>> adjlist;
    GraphAlgorithm(int v,int e,vector<int> hype,map<int,vector<int>> adjlist): v(v),e(e),adjlist(adjlist),hype(hype){}
    virtual void query()=0;

};
class isCycle: public GraphAlgorithm{
    public:
    isCycle(int v,int e,vector<int> hype,map<int,vector<int>> adj):GraphAlgorithm(v,e,hype,adj){}
    void query(){
        vector<int> topo;
        vector<bool> visited(v+1,0);
        vector<int> indegree(v+1);
        priority_queue<int,vector<int>,Comparator> pq;
        for (auto entry:adjlist){
            for (int neigh:entry.second){
                indegree[neigh]++;
            }
        }
        for (int i=1;i<=v;i++){
            if (indegree[i]==0){
                pq.push(i);
            }
        }
        while (!pq.empty()){
            int node=pq.top();
            pq.pop();
            topo.push_back(node);
            for (int neigh:adjlist[node]){
                indegree[neigh]--;
                if (!indegree[neigh]){
                    pq.push(neigh);
                }
            }
        }
        if ((int)topo.size()==v){
            cout<<"NO"<<endl;
        }          
        else{
            cout<<"YES"<<endl;
        }      
    }
};
class indepComponent: public GraphAlgorithm{
    public:
    indepComponent(int v,int e,vector<int> hype,map<int,vector<int>> adj):GraphAlgorithm(v,e,hype,adj){}
    void dfs(int i,vector<bool>& visited,vector<int>& disc,vector<int>& low,stack<int>& st,vector<vector<int>>& scc){
        static int time=0;
        disc[i] = low[i] = ++time;
        st.push(i);
        visited[i]=true;
        for (int neigh:adjlist[i]){
            if (disc[neigh]==-1){
                dfs(neigh,visited,disc,low,st,scc);
                low[i]=min(low[neigh],low[i]);
            }
            else if (visited[neigh]){
                low[i]=min(low[i],disc[neigh]);
            }
        }
        if (low[i] == disc[i]) {
            vector<int> temp;
            while (st.top()!=i) {
                temp.push_back(st.top());
                visited[st.top()] = false;
                st.pop();
            }
            temp.push_back(st.top());
            visited[st.top()] = false;
            st.pop();
            scc.push_back(temp);
        }
    }
    void query(){
        vector<bool> visited(v+1,0);
        vector<int> disc(v+1,-1),low(v+1,-1);
        stack<int> st;
        vector<vector<int>> scc;
        for (int i=1;i<=v;i++){
            if (disc[i]==-1){
                dfs(i,visited,disc,low,st,scc);
            }
        }
        int maxi=0;
        for (auto i:scc){
            maxi=max(maxi,(int)i.size());
        }
        cout<<scc.size()<<" "<<maxi<<endl; 
    } 
};
class validOrder: public GraphAlgorithm{
    public:
    validOrder(int v,int e,vector<int> hype,map<int,vector<int>> adj):GraphAlgorithm(v,e,hype,adj){}
    void query(){
        vector<int> topo;
        vector<bool> visited(v+1,0);
        vector<int> indegree(v+1);
        priority_queue<int,vector<int>,Comparator> pq;
        for (auto entry:adjlist){
            for (int neigh:entry.second){
                indegree[neigh]++;
            }
        }
        for (int i=1;i<=v;i++){
            if (indegree[i]==0){
                pq.push(i);
            }
        }
        while (!pq.empty()){
            int node=pq.top();
            pq.pop();
            topo.push_back(node);
            for (int neigh:adjlist[node]){
                indegree[neigh]--;
                if (!indegree[neigh]){
                    pq.push(neigh);
                }
            }
        }
        if ((int)topo.size()!=v){
            cout<<"NO"<<endl;
        }
        else{
            for (int i=0;i<v;i++){
                cout<<topo[i]<<" ";
            }
            cout<<endl;
        }
    }
    
};
class maxHype: public GraphAlgorithm {
    public:
    maxHype(int v,int e,vector<int> hype,map<int,vector<int>> adj):GraphAlgorithm(v,e,hype,adj){}
    void dfs(int i, vector<bool>& visited,vector<int>& disc,vector<int>& low,stack<int>& st,vector<vector<int>>& scc) {
        static int time = 0;
        disc[i]=low[i]= ++time;
        st.push(i);
        visited[i]=true;
        for (int neigh:adjlist[i]) {
            if (disc[neigh]==-1) {
                dfs(neigh,visited,disc,low,st,scc);
                low[i]=min(low[neigh],low[i]);
            }
            else if (visited[neigh]) {
                low[i]=min(low[i],disc[neigh]);
            }
        }
        if (low[i]==disc[i]){
            vector<int> temp;
            while (st.top()!=i) {
                temp.push_back(st.top());
                visited[st.top()]=false;
                st.pop();
            }
            temp.push_back(st.top());
            visited[st.top()]=false;
            st.pop();
            scc.push_back(temp);
        }
    }
    void query(){
        vector<bool> visited(v+1,0);
        vector<int> disc(v+1,-1),low(v+1,-1);
        stack<int> st;
        vector<vector<int>> sccs;
        for (int i=1;i<=v;i++) {
            if (disc[i]==-1) {
                dfs(i,visited,disc,low,st,sccs);
            }
        }
        int newvertices=sccs.size();
        vector<int> sccHype(newvertices,0);
        map<int,int> nodeToSCC;
        for (int i=0;i<newvertices;i++) {
            for (int node:sccs[i]){
                nodeToSCC[node]=i;
                sccHype[i]+=hype[node];
            }
        }
        map<int,vector<int>> condensedAdj;
        for (int u=1;u<=v;u++) {
            for (int x:adjlist[u]) {
                int sccx=nodeToSCC[x];
                int sccu=nodeToSCC[u];
                if (sccx!=sccu) {
                    condensedAdj[sccu].push_back(sccx);
                }
            }
        }
        vector<int> inDegree(newvertices,0);
        for (auto& entry:condensedAdj) {
            for (int neigh:entry.second) {
                inDegree[neigh]++;
            }
        }
        queue<int> q;
        for (int i = 0;i<newvertices;i++) {
            if (inDegree[i]==0){
                q.push(i);
            }
        }
        vector<int> topoOrder;
        while (!q.empty()){
            int node=q.front();
            q.pop();
            topoOrder.push_back(node);
            for (int neigh:condensedAdj[node]) {
                inDegree[neigh]--;
                if (inDegree[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }
        vector<int> dp(newvertices,0);
        for (int i = 0;i<newvertices;i++) {
            dp[i]=sccHype[i];
        }
        for (int i:topoOrder) {
            for (int j:condensedAdj[i]) {
                dp[j]=max(dp[j],dp[i]+sccHype[j]);
            }
        }
        int maxi=0;
        for (int i=0;i<newvertices;i++) {
            maxi=max(maxi,dp[i]);
        }
        cout<<maxi<<endl;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> hype(n+1);
    map<int,vector<int>> adj;
    for (int i=1;i<=n;i++){
        cin>>hype[i];
    }
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    int q;
    cin>>q;
    while (q--){
        GraphAlgorithm* algo=NULL;
        int type;
        cin>>type;
        if (type==1){
            algo=new isCycle(n,m,hype,adj);
        }
        else if (type==2){
            algo=new indepComponent(n,m,hype,adj);
        }
        else if (type==3){
            algo=new validOrder(n,m,hype,adj);
        }
        else if (type==4){
            algo=new maxHype(n,m,hype,adj);
        }
        algo->query();
        delete algo;
    }
}