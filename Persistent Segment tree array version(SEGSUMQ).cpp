#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1e18
#define N 100005
#define pdi pair< double, ll >
struct node {
    ll suma, sumb;
    ll lc, rc;
    node() {
        suma = 0;
        sumb = 0;
    }
} tree[200*N];
vector< pdi > v;
ll Node_cnt = 0, a[N], b[N], n, i, rt[N];
ll update(ll prv, ll s, ll e, ll pos) {
    if(pos < s || pos > e) return prv;
    ll id = Node_cnt++;
    if(s == e) {
        tree[id].suma = a[s];
        tree[id].sumb = b[s];
        return id;
    }
    ll mid = (s+e)/2;
    tree[id].lc = update(tree[prv].lc, s, mid, pos);
    tree[id].rc = update(tree[prv].rc, mid+1, e, pos);

    tree[id].suma = tree[tree[id].lc].suma + tree[tree[id].rc].suma;
    tree[id].sumb = tree[tree[id].lc].sumb + tree[tree[id].rc].sumb;
    return id;
}
node query(ll cur, ll ss, ll se, ll qs, ll qe) {
    node ret;
    ret.suma = ret.sumb = 0;
    if(qe < ss || qs > se)
        return ret;
    if(ss >= qs && se <= qe)
        return tree[cur];
    ll mid = (ss+se)/2;
    node n1 = query(tree[cur].lc, ss, mid, qs, qe);
    node n2 = query(tree[cur].rc, mid+1, se, qs, qe);

    ret.suma = n1.suma + n2.suma;
    ret.sumb = n1.sumb + n2.sumb;
    return ret;
}
ll build(ll s, ll e)
{
	ll id = Node_cnt++;
	tree[id].suma = tree[id].sumb = 0;
	if(s == e)
		return id;
    ll mid = (s+e)/2;
	tree[id].lc = build(s, mid);
	tree[id].rc = build(mid+1, e);
	return id;
}
int main() {
    cin>>n;
    for(i = 0; i < n; i++)
        cin>>a[i];
    for(i = 0; i < n; i++)
        cin>>b[i];
    for(i = 0; i < n; i++) {
        if(a[i] > 0)
            v.push_back(pdi((1.0*b[i])/a[i], i));
        else
            v.push_back(pdi(MAX, i));
    }
    sort(v.begin(), v.end());
    ll root = build(0, n-1);
    rt[0] = update(root, 0, n-1, v[0].second);
    for(i = 1; i < v.size(); i++) {
        rt[i] = update(rt[i-1], 0, n-1, v[i].second);
    }
    ll q;
    cin>>q;
    fflush(stdout);
    while(q--) {
        ll x, y, c, d;
        cin>>x>>y>>c>>d;
        x--;y--;
        ll low = 0, high = n-1;
        ll ans = 0;
        while(low < high) {
            ll mid = (low+high)/2;
            if(a[v[mid].second]*c <= b[v[mid].second]*d)
                high = mid;
            else
                low = mid+1;
        }
        if(a[v[low].second]*c <= b[v[low].second]*d) low--;
        if(low >= 0) {
            node res = query(rt[low], 0, n-1, x, y);
            ans = res.suma*c - res.sumb*d;
        }
        cout<<ans<<endl;
        fflush(stdout);
    }

    return 0;
}
