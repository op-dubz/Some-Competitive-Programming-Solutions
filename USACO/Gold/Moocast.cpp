#include <iostream> 
#include <map> 
#include <vector> 
#include <numeric> 
using namespace std;
#define pii pair<int, int>
#define ff first 
#define ss second
struct bruh {
    int dis, from, to; 
}; 
int n, largest = -1; 
map<int, pii> m; // id to pair
vector<bruh> edges; 
vector<int> sizes, parents;
int found(int a) {
    if (a == parents[a]) {
        return a;
    }
    return parents[a] = found(parents[a]); 
}
bool unite(int a, int b) { 
    if (sizes[a] < sizes[b]) {
        sizes[b] += sizes[a];
        parents[a] = b; 
        if (sizes[b] == n) {
            return true;
        }
    }
    else {
        sizes[a] += sizes[b]; 
        parents[b] = a; 
        if (sizes[a] == n) {
            return true;
        }
    }
    return false;
}
bool comp(bruh a, bruh b) {
    return a.dis < b.dis;
}
int main() {
    cin >> n; 
    sizes.resize(n); 
    parents.resize(n);
    iota(parents.begin(), parents.end(), 0); 
    fill(sizes.begin(), sizes.end(), 1); 
    for (int i = 0; i < n; i++) { //inputting
        int a, b;
        cin >> a >> b; 
        m[i] = make_pair(a, b); 
    } 
    map<int, pii>::iterator it, it2; 
    for (it = m.begin(); it != m.end(); it++) { //getting all of the edges in a vector O(n^2) 
        it2 = it;
        it2++;
        for (; it2 != m.end(); it2++) {
            pii p1 = it->second, p2 = it2->second; 
            int id1 = it->first, id2 = it2->first; 
            bruh a;
            a.from = id1, a.to = id2, a.dis = (int) (pow((double) (p1.ff - p2.ff), 2) + pow((double) (p1.ss - p2.ss), 2));
            edges.emplace_back(a); //undirected graph
        }
    }
    sort(edges.begin(), edges.end(), comp); //preparation for DSU use
    for (bruh i : edges) {  //DSU is used here
        int head1 = found(i.from), head2 = found(i.to); 
        if (head1 != head2) {
            bool cool = unite(head1, head2);
            largest = max(largest, i.dis); 
            if (cool) {
                cout << largest;
                return 0;
            }
        }
    }
}

