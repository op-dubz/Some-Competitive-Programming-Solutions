#include <iostream> 
#include <set> 
#include <queue> 
#include <vector> 
using namespace std;
#define maxn 100001
#define pii pair<int,int>
#define ss second
#define ff first
#define mp make_pair 
vector<int> paths[maxn], dist(maxn, 2000000000); 
vector<pii> adj[maxn]; 
priority_queue<pii, vector<pii>, greater<pii> > q; 
int n, m; 
set<int> s; 
void recursion(int cur) { 
    if (s.count(cur)) return; 
    s.insert(cur); 
    if (cur == 1) return; 
    for (int i : paths[cur]) {
        recursion(i); 
    }
}
int main() {
    dist[1] = 0; 
    q.push(mp(0, 1)); 
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        int a, b, c; 
        cin >> a >> b >> c; 
        adj[a].push_back(mp(c, b)); 
        adj[b].push_back(mp(c, a)); 
    }  
    while (!q.empty()) {
        pii p = q.top(); 
        q.pop(); 
        for (pii i : adj[p.ss]) {
            if (dist[i.ss] > i.ff + p.ff) {  
                dist[i.ss] = i.ff + p.ff; 
                q.push(mp(i.ff + p.ff, i.ss)); 
            }
        }
    } 
    //for (int i = 1; i <= n; i++) cout << dist[i] << " "; 
    q.push(mp(0, 1)); 
    while (!q.empty()) {  
        pii p = q.top(); 
        q.pop(); 
        for (pii i : adj[p.ss]) {
            if (dist[i.ss] == i.ff + p.ff) {  
                q.push(mp(i.ff + p.ff, i.ss)); 
                paths[i.ss].push_back(p.ss); 
            }
        }
    }  
    recursion(n); 
    for (int i : s) cout << i << " "; 
    
}