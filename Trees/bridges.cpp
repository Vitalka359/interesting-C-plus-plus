#include<bits/stdc++.h>
using namespace std;
 
const int M = 20000;
vector <vector<int>> graph;
bool visited[M];
int tin[M], tout[M], timer;
vector<pair<int, int>> arr;
set<pair<int, int>> aa;

void dfs(int i, int par = -1){
    visited[i] = true;
    tin[i] = timer;
    tout[i] = timer;
    timer++;
    timer++;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u];
        if(x == par) continue;
        if(visited[x] == true){
            tout[i] = min(tout[i], tin[x]);
        }else{
            dfs(x, i);
            tout[i] = min(tout[i], tout[x]);
            if(tout[x]>tin[i]) 
                aa.insert({min(i, x), max(x, i)});
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        arr.push_back({min(u,v), max(u,v)});
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    timer = 0;
    for(int i = 0; i<n; i++) 
        visited[i] = false;
    for(int i = 0; i<n; i++)
        if(visited[i] == false)
            dfs(i);
    cout << aa.size() << "\n";
    for (int i = 0; i<m; i++)
        if(aa.count(arr[i])) 
        cout << i+1 << " ";
}
