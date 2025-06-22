#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <climits>
using namespace std;
#define maxn 100001 
#define pii pair<int,int> 
#define ff first
#define ss second

int n, k, res = 0; 
vector<int> adj[maxn]; 
map<int, pii> m; // distanceFromK >= distanceFromLeaf
void dfs(int cur, int par) { 
    if (cur != k) { 
        m[cur].ff = 1 + m[par].ff; 
    } 
    if (adj[cur].size() == 1) { 
        m[cur].ss = 0; 
        return; 
    } 
    for (int i : adj[cur]) {
        if (i != par) { 
            dfs(i, cur); 
            m[cur].ss = min(m[cur].ss, m[i].ss + 1); 
        }
    } 
}
void dfs2(int cur, int par) {
    
    for (int i : adj[cur]) {
        if (i != par) {
            if (m[i].ff >= m[i].ss) {
                res++;
            }
            else {
                dfs2(i, cur); 
            }
        }
    }
}
int main() {
    cin >> n >> k; 
    for (int i = 0; i < n-1; i++) {
        int a, b; 
        cin >> a >> b; 
        adj[a].push_back(b);
        adj[b].emplace_back(a); 
    }
    for (int i = 1; i <= n; i++) {
        m[i].ff = 0;
        m[i].ss = INT_MAX;
    }
    
    dfs(k, -1); 
    dfs2(k, -1); 
    // for (int i = 1; i <= n; i++) {
    //     cout << i << ":  fromRoot: " << m[i].ff << "  fromLeaf: " << m[i].ss << endl;
    // }
    cout << res; 
}