#include <bits/stdc++.h>
using namespace std;
 
vector<__int64> segmentTree;
vector<__int64> arr;
 
__int64 build_min(int v, int vl, int vr) {
    if (vl == vr) {
        segmentTree[v] = arr[vl];
        return segmentTree[v];
    }
 
    int vm = (vl+vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
 
    __int64 lValue = build_min(indL, vl, vm);
    __int64 rValue = build_min(indR, vm+1, vr);
 
    segmentTree[v] = min(lValue, rValue);
    return segmentTree[v];
}
__int64 minimum(int v, int vl, int vr, int ql, int qr) {
    if (vr < ql || qr < vl) return 1e6+1; 
 
    if (ql <= vl && vr <= qr) return segmentTree[v];
 
    int vm = (vl + vr)/2;
    int indR = 2*v+1;
    int indL = 2*v+2;
    __int64 lValue = minimum(indL, vl, vm, ql, qr);
    __int64 rValue = minimum(indR, vm+1, vr, ql, qr);
    return min(lValue, rValue);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
 
    segmentTree.resize(4*n);
    build_min(0, 0, n-1);
    
    vector<__int64>sum(n);
    sum[0] = arr[0];
    for(int i = 1; i<n; i++) sum[i] = sum[i-1]+arr[i];
    
    __int64 ans = arr[0]*arr[0];
    int aa = 1, bb = 1;
    for(int i = 0; i<n; i++){
        int l = i, ll = 0, r = i, rr = n-1;
        int mr = (r+rr)/2, ml = (l+ll)/2;
        while(l!=ml && ll!=ml){
            if(minimum(0, 0, n-1, ml, i) == arr[i]){
                l = ml; ml = (l+ll)/2;
            } else {
                ll = ml; ml = (l+ll)/2;
            }
        }
        if(minimum(0, 0, n-1, ll, i) == arr[i]) l = ll;
        while(r!=mr && rr!=mr){
            if(minimum(0, 0, n-1, i, mr) == arr[i]){
                r = mr; mr = (r+rr)/2;
            } else {
                rr = mr; mr = (r+rr)/2;
            }
        }
        if(minimum(0, 0, n-1, i, rr) == arr[i]) r = rr;
        __int64 b = sum[r];
        if(l>0) b-=sum[l-1];
        if(arr[i]*b>=ans){
            ans = arr[i]*b;
            aa = l+1;
            bb = r+1;
        }
    }
    cout << ans << '\n' << aa << " " << bb;
}
