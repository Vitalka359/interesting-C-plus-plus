#include<bits/stdc++.h>
using namespace std;
 
const int M = 20000;
vector <vector<int>> graph;
bool visited[M];
int tin[M], tout[M], timer, colour[M], col = 1;
multiset<pair<int, int>> bridges;
multiset<pair<int, int>> notbridges;
 
void dfs1(int i){
    colour[i] = col;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u], y = min(x, i), yy = max(x, i);
        if(colour[x] == 0 && not bridges.count({y, yy})) 
            dfs1(x);
    }
}
 
void dfs(int i, int par = -1){
    visited[i] = true;
    tin[i] = timer;
    tout[i] = timer;
    timer++;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u];
        if(x == par) continue;
        int y = min(x, i), yy = max(x, i);
        if(bridges.count({y, yy})){
            bridges.erase({y, yy});
            notbridges.insert({y, yy});
        }
        if(visited[x] == true){
            tout[i] = min(tout[i], tin[x]);
        }else{
            dfs(x, i);
            tout[i] = min(tout[i], tout[x]);
            if(tout[x]>tin[i]) {
                if(bridges.count({y, yy})){
                    bridges.erase({y, yy});
                    notbridges.insert({y, yy});
                }else bridges.insert({y, yy});
            }
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
        graph[u].push_back(v);
        if(u!=v)
        graph[v].push_back(u);
    }
    timer = 0;
    for(int i = 0; i<n; i++)
        if(visited[i] == false)
            dfs(i, -1);
            
    //cout << bridges.size() << " " << notbridges.size() << "\n";
    for(int i = 0; i<n; i++)
        if(colour[i] == 0){
            dfs1(i);
            col++;
        }
    cout << col-1 <<"\n";
    for(int i = 0; i<n; i++) cout << colour[i] << " ";
}
