#include <bits/stdc++.h>
using namespace std;

__int64 build(vector<pair<__int64, __int64>> &segmentTree, vector<int>&arr, int v, int vl, int vr) {
    if (vl == vr) {
        segmentTree[v].first = arr[vl];
        return segmentTree[v].first;
    }

    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;

    __int64 lValue = build(segmentTree, arr, indL, vl, vm);
    __int64 rValue = build(segmentTree, arr, indR, vm+1, vr);

    segmentTree[v].first = min(lValue, rValue);
    return segmentTree[v].first;
}

__int64 minimum(vector<pair<__int64, __int64>> &segmentTree, int v, int vl, int vr, int ql, int qr) {
    if (vr < ql || qr < vl) return 1e9+1; 

    if (ql <= vl && vr <= qr) return segmentTree[v].first;

    int vm = (vl + vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    __int64 lValue = minimum(segmentTree, indL, vl, vm, ql, qr);
    __int64 rValue = minimum(segmentTree, indR, vm+1, vr, ql, qr);
    return min(lValue, rValue);
}

void modify(vector<pair<__int64, __int64>> &segmentTree, int v, int vl, int vr, int q, __int64 x){
    if (vr < q || q < vl) return;
    if(vl == vr){
    segmentTree[v].first = x;
    return;
    }
    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    
    if (q <= vm)
    modify(segmentTree, indL, vl, vm, q, x);
    if (q >= vm+1)
    modify(segmentTree, indR, vm+1, vr, q, x);

    segmentTree[v].first = min(segmentTree[indL].first, segmentTree[indR].first);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<pair<__int64, __int64>> segmentTree(4*n);
    build(segmentTree, arr, 0, 0, n-1);
    string ss;
    int q, x;
    while(cin >> ss >> q >> x){
        if (ss == "min") {
            q--; x--;
            cout << minimum(segmentTree, 0, 0, n-1, q, x) << '\n';
        } else {
            q--;
            modify(segmentTree, 0, 0, n-1, q, x);
        }
    }
}
