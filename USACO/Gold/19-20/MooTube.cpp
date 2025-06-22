#include <iostream> 
#include <vector> 
#include <numeric> 
using namespace std;
#define maxn 100001
int n, q;
vector<int> parent(maxn), sizes(maxn, 1);
struct input {
    int k, index, num, answer = 0;
};
struct edge {
    int a1, a2, k; 
}; 
bool comp(input a, input b) {
    return a.k > b.k;
}
bool comp2(input a, input b) {
    return a.num < b.num;
}
bool comp3(edge a, edge b) {
    return a.k > b.k;
} 
int found(int u) {
    if (u == parent[u]) {
        return u;
    }
    return parent[u] = found(parent[u]);
}
void unite(int a, int b) { //a and b are both parents of the their respective groups
    if (sizes[a] < sizes[b]) {
        parent[a] = b; 
        sizes[b] += sizes[a];
        return;
    }
    parent[b] = a; 
    sizes[a] += sizes[b];
}
int main() {
    cin >> n >> q;
    iota(parent.begin(), parent.end(), 0);
    vector<input> v(q); 
    vector<edge> edges;
    for (int i = 0; i < n - 1; i++) {
        edge a;
        cin >> a.a1 >> a.a2 >> a.k;
        edges.emplace_back(a); 
    }
    sort(edges.begin(), edges.end(), comp3); 
    for (int j = 0; j < q; j++) {
        cin >> v[j].k >> v[j].index;
        v[j].num = j; 
    }
    sort(v.begin(), v.end(), comp);
    int point = 0;
    for (int i = 0; i < v.size(); i++) {
        while (point < edges.size() && edges[point].k >= v[i].k) {
            unite(found(edges[point].a1), found(edges[point].a2));
            point++;
        } 
        v[i].answer = sizes[found(v[i].index)] - 1;
    }
    sort(v.begin(), v.end(), comp2);
    for (int i = 0; i < q; i++) {
        cout << v[i].answer << endl;
    }
}

