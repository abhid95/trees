#include<bits/stdc++.h>
using namespace std;
#define ll int
#define pic pair< ll, char >
#define pii pair< ll, ll >
#define N 500005
set< pii > st[(1 << 22) + 10];
vector< ll > *vec[N];
ll sz[N], gb[N], hc[N], dpth[N], ans[N], n, i, p;
char c;
vector< pic > g[N];
ll dfs(ll i, ll b, ll prv, ll lvl) {
    sz[i] = 1;
    gb[i] = b;
    hc[i] = -1;
    dpth[i] = lvl;
    ll mx = -1;
    for(ll j = 0; j < g[i].size(); j++) {
        ll child = g[i][j].first;
        if(child == prv) continue;
        ll val = dfs(child, b^(1<<(g[i][j].second-'a')), i, lvl+1);
        if(val > mx) {
            mx = val;
            hc[i] = child;
        }
        sz[i] += val;
    }
    return sz[i];
}
void dfs2(ll i, ll prv, ll flag) {
    ans[i] = 0;
    for(ll j = 0; j < g[i].size(); j++) {
        ll child = g[i][j].first;
        if(child == prv) continue;
        if(child == hc[i]) continue;
        dfs2(child, i, 0);
        ans[i] = max(ans[i], ans[child]);
    }
    if(hc[i] != -1) {
        dfs2(hc[i], i, 1);
        vec[i] = vec[hc[i]];
    }
    st[gb[i]].insert(pii(-dpth[i], i));
    vec[i]->push_back(i);
    if (hc[i] != -1) {
        ans[i] = max(ans[i], ans[hc[i]]);
        ll cc = i;
        ll bt = gb[cc];
        if(st[bt].size())
            ans[i] = max(ans[i], dpth[cc] - (*st[bt].begin()).first - 2*dpth[i]);
        for(ll l = 0; l < 22; l++) {
            if(st[bt^(1<<l)].size())
                ans[i] = max(ans[i], dpth[cc] - (*st[bt^(1<<l)].begin()).first - 2*dpth[i]);
        }
    }
    for(ll j = 0; j < g[i].size(); j++) {
        ll child = g[i][j].first;
        if(child == prv) continue;
        if(child == hc[i]) continue;
        for(ll k = 0; k < vec[child]->size(); k++) {
            ll cc = (*vec[child])[k];
            ll bt = gb[cc];
            if(st[bt].size())
                ans[i] = max(ans[i], dpth[cc] - (*st[bt].begin()).first - 2*dpth[i]);
            for(ll l = 0; l < 22; l++) {
                if(st[bt^(1<<l)].size())
                    ans[i] = max(ans[i], dpth[cc] - (*st[bt^(1<<l)].begin()).first - 2*dpth[i]);
            }
        }
        for(ll k = 0; k < vec[child]->size(); k++) {
            ll cc = (*vec[child])[k];
            ll bt = gb[cc];
            st[bt].insert(pii(-dpth[cc], cc));
            vec[i]->push_back(cc);
        }
    }
    if(flag == 0) {
        for(ll j = 0; j < vec[i]->size(); j++) {
            ll u = (*vec[i])[j];
            st[gb[u]].erase(pii(-dpth[u], u));
        }
    }

}
int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    for (int i = 0; i < N; ++i) vec[i] = new vector <ll>();
    for(i = 1; i < n; i++) {
        cin>>p>>c;
        p--;
        g[i].push_back(pic(p, c));
        g[p].push_back(pic(i, c));
    }
    dfs(0, 0, -1, 0);
    dfs2(0, -1, 0);
    for(i = 0; i < n; i++) {
        cout<<ans[i]<<" ";
    }
    return 0;
}
