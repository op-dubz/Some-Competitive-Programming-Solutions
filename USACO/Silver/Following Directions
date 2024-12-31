// https://usaco.org/index.php?page=viewproblem2&cpid=1279
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
struct both {
   ll cost, prefixSum = 0;
   bool visited = false;
   char dir = '.';
};
ll n, q, comp = 0, COST, res = 0;
vector<vector<both> > grid(1502, vector<both>(1502));
void initial(ll row, ll col) {
   grid[row][col].visited = true;
   grid[row][col].cost = COST;
   grid[row][col].prefixSum += COST;          
   if (col > 1 && grid[row][col-1].dir == 'R') {
       initial(row, col - 1);
       grid[row][col].prefixSum += grid[row][col-1].prefixSum;
   }
   if (row > 1 && grid[row - 1][col].dir == 'D') {
       initial(row - 1, col);
       grid[row][col].prefixSum += grid[row - 1][col].prefixSum;
   }
}
void dfs(ll row, ll col, ll add) {
   grid[row][col].prefixSum += add;
   if (row == n+1 || col == n+1) return;
   if (grid[row][col].dir == 'R') dfs(row, col + 1, add);
   else if (grid[row][col].dir == 'D') dfs(row + 1, col, add);
}
void dfs2(ll row, ll col, ll add) {
   grid[row][col].prefixSum = add, grid[row][col].cost = add;
   if (col > 0 && grid[row][col-1].dir == 'R') {
       dfs2(row, col - 1, add);
       grid[row][col].prefixSum += grid[row][col-1].prefixSum;
   }
   if (row > 0 && grid[row - 1][col].dir == 'D') {
       dfs2(row - 1, col, add);
       grid[row][col].prefixSum += grid[row - 1][col].prefixSum;
   }
}
int main() {
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   cin >> n;
   for (int i = 1; i <= n; i++) {
       for (int j = 1; j <= n; j++) {
           cin >> grid[i][j].dir;
       }
       cin >> grid[i][n+1].cost;
   }
   for (int i = 1; i <= n; i++) {
       cin >> grid[n+1][i].cost;
   }
   for (int i = 1; i <= n; i++) {
       COST = grid[n+1][i].cost;
       initial(n+1, i);
       COST = grid[i][n+1].cost;
       initial(i, n+1);   
       res += grid[i][n+1].prefixSum + grid[n+1][i].prefixSum - grid[i][n+1].cost - grid[n+1][i].cost;
   } 
   cout << res << endl;
   cin >> q;
   ll col, row;
   while (q--) {
       cin >> row >> col;
       if (grid[row][col].dir == 'R') {
           dfs(row, col + 1, -grid[row][col].prefixSum);
           res += -grid[row][col].prefixSum + grid[row][col].prefixSum / grid[row][col].cost * grid[row+1][col].cost;
           dfs(row + 1, col, grid[row][col].prefixSum / grid[row][col].cost * grid[row+1][col].cost);
           grid[row][col].dir = 'D';
           dfs2(row, col, grid[row+1][col].cost);
       }
       else { // == 'D'  
           dfs(row + 1, col, -grid[row][col].prefixSum);
           res += -grid[row][col].prefixSum + grid[row][col].prefixSum / grid[row][col].cost * grid[row][col+1].cost;
           dfs(row, col + 1, grid[row][col].prefixSum / grid[row][col].cost * grid[row][col+1].cost);
           grid[row][col].dir = 'R';
           dfs2(row, col, grid[row][col+1].cost);
       }
       cout << res << endl;
   }
}
