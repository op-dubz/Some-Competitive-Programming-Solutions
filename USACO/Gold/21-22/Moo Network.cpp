#include <iostream> 
#include <vector> 
#include <map> 
#include <numeric> 
#include <algorithm> 
using namespace std;
typedef long long ll;
#define maxv 100000
#define pii pair<ll,ll> 
#define ff first
#define ss second
const ll range = 40;
ll v, sum = 0;
vector<ll> sizes(maxv, 1), parent(maxv);
vector<pii> input;
struct edge {
    ll a, b, c;
};
ll head(ll a) {
    if (a == parent[a]) {
        return a;
    }
    return parent[a] = head(parent[a]); 
}
bool unite(ll a, ll b) {
    if (sizes[a] < sizes[b]) {
        sizes[b] += sizes[a];
        parent[a] = b;
        if (sizes[b] == v) {
            return true;
        }
    }
    else {
        sizes[a] += sizes[b];
        parent[b] = a;
        if (sizes[a] == v) {
            return true;
        }
    }
    return false;
}
bool comp(edge a, edge b) {
    return a.c < b.c; 
}
bool comp2(pii a, pii b) {
    return a.ff < b.ff;
}
vector<edge> edges; 
map<ll, pii> m; 
int main() {
    cin >> v; 
    input.resize(v);
    iota(parent.begin(), parent.end(), 0);
    for (ll i = 0; i < v; i++) {
        cin >> input[i].ff >> input[i].ss;
    }
    sort(input.begin(), input.end(), comp2); //sort by x  
    for (ll i = 0; i < v; i++) {
        for (ll j = i + 1; j < min(v, i + range); j++) {
            edge a;
            a.a = i, a.b = j, a.c = (ll) (pow(input[i].ff - input[j].ff, 2) + pow(input[i].ss - input[j].ss, 2)); 
            edges.emplace_back(a);
        }
    }
    sort(edges.begin(), edges.end(), comp);
    for (edge i : edges) {
        ll a = head(i.a), b = head(i.b);
        if (a != b) {
            sum += i.c;
            if (unite(a, b)) {
                cout << sum; 
                return 0; 
            }
        }
    }
}

