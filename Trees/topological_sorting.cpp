#include<bits/stdc++.h>
using namespace std;

vector <vector<int>> graph;
vector <pair<int, int>> glub;
vector<int>visited;
int start = 0;
 
void dfs(int i){
    visited[i] = 1;
    for(int u = 0; u<graph[i].size(); u++){
        int x = graph[i][u];
        if(visited[x] == 0) dfs(x);
        if(visited[x] == 1){
            cout << "-1";
            exit(0);
        }
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
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    glub.resize(n);
    visited.resize(n);
    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
    }
    for(int i = 0; i<n; i++)
    if(visited[i] == 0)
        dfs(i);
        
    sort(glub.begin(), glub.end());
    for(int i = n-1; i>=0; i--) cout << glub[i].second+1 << " ";
}
