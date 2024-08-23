#include <bits/stdc++.h>
using namespace std;

vector<pair<__int64, __int64>> segmentTree;
vector<int> arr;

__int64 build(int v, int vl, int vr) {
    if (vl == vr) {
        segmentTree[v].first = arr[vl];
        return segmentTree[v].first;
    }

    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    __int64 lValue = build(indL, vl, vm);
    __int64 rValue = build(indR, vm+1, vr);

    segmentTree[v].first = lValue + rValue;
    return segmentTree[v].first;
}

void push(int v, int vl, int vr) {
    if (segmentTree[v].second == 0) return;

    __int64 change = segmentTree[v].second;
    segmentTree[v].first += change*(vr-vl+1);
    segmentTree[v].second = 0;

    if (vl != vr) {
        segmentTree[2*v+1].second += change;
        segmentTree[2*v+2].second += change;
    }
}

__int64 sum(int v, int vl, int vr, int ql, int qr) {
    push(v, vl, vr);
    if (vr<ql || qr<vl) return 0;

    if (ql <= vl && vr <= qr) return segmentTree[v].first;

    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    __int64 lValue = sum(indL, vl, vm, ql, qr);
    __int64 rValue = sum(indR, vm+1, vr, ql, qr);

    return lValue+rValue;
}

void modify(int v, int vl, int vr, int q, __int64 x) {
    push(v, vl, vr);
    if (vr < q || q < vl) return;
    if(vl == vr){
    segmentTree[v].first = x;
    return;
    }
    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    
    if (q <= vm)
    modify(indL, vl, vm, q, x);
    if (q >= vm+1)
    modify(indR, vm+1, vr, q, x);
 
    segmentTree[v].first = segmentTree[indL].first + segmentTree[indR].first;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    segmentTree.resize(4*n);
    build(0, 0, n-1);
    string ss;
    int q, x;
    while(cin >> ss >> q >> x){
        if (ss == "sum") {
            q--; x--;
            cout << sum(0, 0, n-1, q, x) << '\n';
        } else {
            q--;
            modify(0, 0, n-1, q, x);
        }
    }
}
