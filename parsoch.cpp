#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>

using namespace std;

int n = 0, m = 0;
vector<int> mt;
vector<char> used;

class BipartiteMatcher {
public:
    int n, m;
    vector<vector<int>> g;
    vector<int> matchU, matchV;
    vector<bool> visited;

    BipartiteMatcher(int n, int m) : n(n), m(m) {
        g.resize(n);
        matchU.resize(n, -1);
        matchV.resize(m, -1);
        visited.resize(n, false);
    }

    bool dfs(int u) {
        if (visited[u]) return false;
        visited[u] = true;
        for (int v : g[u]) {
            if (matchV[v] == -1 || dfs(matchV[v])) {
                matchU[u] = v;
                matchV[v] = u;
                return true;
            }
        }
        return false;
    }

    int maximumMatching() {
        int matchCount = 0;
        for (int u = 0; u < n; ++u) {
            fill(visited.begin(), visited.end(), false);
            if (dfs(u)) {
                ++matchCount;
            }
        }
        return matchCount;
    }

    void printMatching() {
        for (int u = 0; u < n; ++u) {
            if (matchU[u] != -1) {
                cout << u + 1 << " " << matchU[u] + 1 << "\n";
            }
        }
        return;
    }

};

    bool try_kuhn(int v, vector<vector<int>> g) {
        if (used[v])  return false;
        used[v] = true;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (mt[to] == -1 || try_kuhn(mt[to], g)) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }

int main() {
    setlocale(LC_ALL, "");
    int n, m, cnt;
    cout << "Введите количество вершин первой и второй доли, а также количество рёбер: ";
    cin >> n >> m >> cnt;
    BipartiteMatcher matcher(n, m);
    matcher.g.resize(n);
    cout << "Введите рёбра:\n";
    for (int i = 0; i < cnt; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        matcher.g[a].push_back(b);
    }
    clock_t start_time = clock();
    int maxMatching = matcher.maximumMatching();
    cout << "Максимальное паросочетание по алгоритму Форда-Фалкерсона: " << maxMatching << endl;
    matcher.printMatching();
    clock_t end_time = clock();
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds\n";

    start_time = clock();
    mt.resize(m, -1);
    for (int v = 0; v < n; ++v) {
        used.resize(n, false);
        try_kuhn(v, matcher.g);
    }
    cout << "Максимальное паросочетание по алгоритму Куна: " << maxMatching << endl;
    for (int i = 0; i < m; ++i)
        if (mt[i] != -1)
            printf("%d %d\n", mt[i] + 1, i + 1);
    end_time = clock();
    time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds\n";

}
