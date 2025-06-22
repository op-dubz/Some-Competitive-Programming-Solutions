#include <iostream>
#include <vector> 
#include <map>
using namespace std;
typedef long long ll; 
#define maxn 100001
struct node {
    ll len, leaves = 0, cost = 0; 
};
vector<ll> adj[maxn];
vector<node> description; 
ll n, res = 0, maxl; //bessieIndex = 1
    
void dfs(int cur, int par) {
    for (int i : adj[cur]) {
        if (i != par) {        
            dfs(i, cur); 
            description[cur].leaves += description[i].leaves; 
            if (cur != 1) {
                //description[1].cost += description[cur].len; // incorrect
                description[1].cost += description[i].leaves; 
            } 
            
        }
    }
    if (cur != 1) {
      description[1].cost += description[cur].leaves * description[cur].len; 
    }
    if (adj[cur].size() == 1) { 
        description[cur].leaves++; 
        description[1].cost += description[cur].len; 
        //description[1].cost += description[cur].len; 
        return; 
    } 
}  
void dfs2(int cur, int par) {
    for (int i : adj[cur]) {
        if (i != par) {
            description[i].cost = description[cur].cost+3*(maxl-description[i].leaves)-(description[i].len+1)*description[i].leaves; 
            if (adj[i].size() != 1) {
                res = min(res, description[i].cost); 
                dfs2(i, cur); 
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); 
    cin >> n;
    description.resize(n+1);
    for (int i = 0; i < n; i++) {
        string s; 
        ll m, a;
        cin >> s >> m; 
        description[i+1].len = s.length();  
        for (int j = 0; j < m; j++) {
            cin >> a;
            adj[i+1].emplace_back(a); 
            adj[a].emplace_back(i+1); 
        }
    }
    adj[1].emplace_back(-1); 
    dfs(1, -1); 
    // cout << description[1].cost; 
    res = description[1].cost;
    maxl = description[1].leaves;
    dfs2(1, -1); 
    cout << res; 
    //cout << description[2].cost; 
}