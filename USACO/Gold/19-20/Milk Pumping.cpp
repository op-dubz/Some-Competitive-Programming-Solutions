#include <iostream>
#include <set> 
#include <queue> 
#include <vector> 
using namespace std;
#define maxn 1001
typedef long long ll;
double res = 0;
set<int> s;
int n, m;
struct hope {
    int flow, cost, target;
};
struct comp {
    bool operator()(hope a, hope b) {
        return a.cost > b.cost;
    }
};
vector<hope> adj[maxn]; //
void go(int most) {
    priority_queue<hope, vector<hope>, comp> q; //distance, node
    vector<int> distances(maxn, INT_MAX);
    hope b;
    distances[1] = 0;
    b.target = 1, b.flow = INT_MAX, b.cost = 0;
    q.push(b);
    while (!q.empty()) {
        int u = q.top().target, d = distances[u];
        q.pop();
        for (hope j : adj[u]) {
            if (distances[j.target] > d + j.cost && j.flow >= most) {
                distances[j.target] = d + j.cost;
                hope e;
                e.cost = distances[j.target], e.target = j.target, e.flow = j.flow;
                q.push(e);
            }
        }
    }
    if (distances[n] != INT_MAX) {
        res = max(res, floor(1.0 * most / distances[n] * 1000000));
    }
}
int main() {
    cin >> n >> m;
    int a;
    for (int i = 0; i < m; i++) { //input
        hope b;
        cin >> a >> b.target >> b.cost >> b.flow; 
        adj[a].push_back(b);
        swap(a, b.target);
        adj[a].push_back(b);
        s.insert(b.flow);
    }
    for (int i : s) {
        int most = i;
        go(most);
        
    }
    cout << res;
}