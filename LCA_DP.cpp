#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll mn, mx, par[100005], n, q, x, arr[100005], level[100005], ii, i, j, k, a, b;
vector<ll> g[100005], v;
ll f[1000000][20];
map<ll, ll> mp;
void dfs(ll i) {
    v.push_back(i);
    for(ll j = 0; j < g[i].size(); j++) {
        dfs(g[i][j]);
    }
}
void dfs2(ll u,ll n){
	int i,j;
	for(j=1;(1<<j)<n;j++)
		f[u][j]=f[f[u][j-1]][j-1];
	for(i=0;i<g[u].size();i++){
		if(!level[g[u][i]])
		{
			f[g[u][i]][0]=u;
			level[g[u][i]]=level[u]+1;
			dfs2(g[u][i],n);
		}
	}
}
ll lca(ll p,ll q){
	ll i,j,log;
	if(level[p]<level[q])
        swap(p,q);
	log=(ll)log2(level[p]);
	for(i=log;i>=0;i--)
        if(level[p]-(1<<i)>=level[q])
            p=f[p][i];
	if(p==q)
        return p;
	for(i=log;i>=0;i--)
	{
		if(f[p][i]!=-1 && f[p][i]!=f[q][i])
            p=f[p][i],q=f[q][i];
	}
	return f[p][0];

}
level[1] = 1;
