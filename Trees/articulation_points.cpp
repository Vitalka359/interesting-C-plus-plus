#include<bits/stdc++.h>
using namespace std;
 
const int M = 20000;
vector <vector<int>> graph;
bool visited[M];
int tin[M], tout[M], timer;
vector<int> arr;
set<int>aa;
 
void dfs(int i, int par = -1){
    visited[i] = true;
    tin[i] = timer;
    tout[i] = timer;
    timer++;
    int potomki = 0;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u];
        if(x == par) continue;
        if(visited[x] == true){
            tout[i] = min(tout[i], tin[x]);
        }else{
            dfs(x, i);
            tout[i] = min(tout[i], tout[x]);
            if(tout[x]>=tin[i] && par!=-1) arr.push_back(i);
            potomki++;
        }
    }
    if(par == -1 && potomki>1) arr.push_back(i);
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
        graph[v].push_back(u);
    }
    timer = 0;
    for(int i = 0; i<n; i++) 
        visited[i] = false;
    for(int i = 0; i<n; i++)
        if(visited[i] == false) dfs(i);
            
    sort(arr.begin(), arr.end());
    int y = arr.size();
    for (int i = 0; i<arr.size(); i++){
        if(aa.count(arr[i])){ y--; arr[i] = -1;}
            aa.insert(arr[i]);
    }
    cout << y << "\n";
    for (int i = 0; i<arr.size(); i++)
    if(arr[i]!=-1) cout << arr[i]+1 << " ";
}
