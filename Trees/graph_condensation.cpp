#include<bits/stdc++.h>
using namespace std;
 
vector <vector<int>> graph;
vector <vector<int>> inversegraph;
vector <pair<int, int>> glub;
vector<int>visited;
vector<int>used;
set<pair<int, int>> aa;
int start = 0, colour = 1;
 
void kond(int i){
    used[i] = colour;
    for(int u = 0; u<inversegraph[i].size(); u++){
        int x = inversegraph[i][u];
        if(used[x] == 0) kond(x);
    }
}
 
void dfs(int i){
    visited[i] = 1;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u];
        if(visited[x] == 0) dfs(x);
    }
    start++;
    glub[i].first = start;
    glub[i].second = i;
    visited[i] = 2;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    inversegraph.resize(n);
    graph.resize(n);
    glub.resize(n);
    visited.resize(n);
    used.resize(n);
    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        inversegraph[v].push_back(u);
    }
    for(int i = 0; i<n; i++)
    if(visited[i] == 0)
        dfs(i);
    sort(glub.begin(), glub.end());
    
    for(int i = n-1; i>=0; i--){
        int x = glub[i].second;
        if(used[x] == 0){ 
            kond(x);
            colour++;
        }
    }
    for(int i = 0; i<n; i++){
        for(int u = 0; u<graph[i].size(); u++){
          int ii = used[i], uu = used[graph[i][u]];
            if(ii!=uu &&  not aa.count({min(ii,uu), max(ii,uu)})) ans++;
            aa.insert({min(ii,uu), max(ii,uu)});
        }
    }
    cout << ans << "\n";
    //for(int i = 0; i<n; i++) cout << used[i] << " ";
}
