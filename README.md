#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, child[N],m,LN;
bool visit[N];
vector<int> a[N],ans(N,INT_MAX);
vector <int> g[N];
int par[N][20];
vector <int> parent(N),depth(N,0);
// tim centroid
void dfs(int u, int p) {
    child[u] = 1;
    for(int i = 0; i < a[u].size(); i++) {
    	int v = a[u][i]; 
	    if(v != p && !visit[v]) 
		{
			depth[v] = depth[u] + 1;
			par[u][0] = v;
            dfs(v, u);
            child[u] += child[v]; 
		}
    }
}

int findcen(int u, int p, int sz) {
    for(int i = 0; i < a[u].size() ;i++) {
    	int v = a[u][i]; 
	    if(v != p && !visit[v]) {
                 if(child[v] > sz / 2) return findcen(v, u, sz);
        }
    }
    return u;
}

int centroid(int root) { 
	dfs(root, root);
    int cen = findcen(root, root, child[root]);
    /*
    .....
    */
    visit[cen] = true;
    for(int i = 0; i < a[cen].size() ; i++) {
    	int v = a[cen][i];
	    if(!visit[v])
	    {
            	g[cen].push_back(centroid(v));
        } 
    }
    return cen;
}
// ket thuc tim centroid
// dfs de tim do sau
void dfs_second(int u , int p) { 
        for(int j = 0;j < g[u].size();j++) {
        	int k = g[u][j];
        	if(k != p) {
        		parent[k] = u;
        		dfs(k,u);
			}
		}
	
}
void RMQ() {
	LN = trunc(log2(n)) +1;
	for(int i = 1; i <= n; i ++) {
		for(int j = 0; j <= LN ; j++) {
			par[i][j] = par[par[i][j-1]][j-1];
		}
	}
}
int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int delta = depth[u] - depth[v];
	for(int i = LN ;i >= 0; i--) {
		if((delta >> i) & 1) u = par[u][i];
	}
	if(u == v) return u;
	for(int i = LN; i >= 0; i--) {
		if(par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return u = par[u][0];
}
int dis(int u, int v) {
	return (depth[u] + depth[v] - 2*depth[LCA(u,v)]);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	centroid(1);
	dfs(1,-1);
	int cen1 = findcen(1,1,child[1]);
	dfs_second(cen1,-1);
	RMQ();
	for(int i = 1; i <= m;i++) {
		int t,num;
		cin >> t >> num;
		if(t == 1) {
			for(int v = parent[num] ; v != cen1; v = parent[v]) {
				ans[v] = min(ans[v],dis(num,v));
			}
			ans[cen1] = min(ans[cen1] , dis(cen1,num));
		}
		else if(t == 2) {
			int mn = 543423;
			for(int v = parent[num] ; v != cen1; v = parent[v]){
				mn = min(mn,ans[v] + dis(num,v));
			}
			mn = min(mn, ans[cen1] + dis(cen1,num));
			cout << mn << endl;
		}
	}
}













