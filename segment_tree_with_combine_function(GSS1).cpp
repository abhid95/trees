#include <bits/stdc++.h>
#define MAX 1000000007
#define pb push_back
#define mp make_pair
#define FOR(n) for(i=0;i<n;i++)
#define rep(i,n) for(i=0;i<n;i++)
#define reps(i,a,b) for(i=a;i<=b;i++)
#define swap(a,b) T=a,a=b,b=T
#define ll long long int
#define que queue<int>
#define s(t) scanf("%lld",&t)
#define p(t) printf("%lld\n",t)
using namespace std;
ll mx(ll a[],ll k)
{
    ll i,m,pos;
    m=0;
    FOR(k)
        if(a[i]>m)
            {m=a[i];pos=i;}
    return m;
}
struct node
{
    ll sum;
    ll best;
    ll left;
    ll right;
};
int n;
ll arr[100005];
node tree[500006];
node combine(node l,node r)
{
    node tmp;
    tmp.sum=l.sum+r.sum;
    tmp.left=max(l.left,l.sum+r.left);
    tmp.right=max(r.right,r.sum+l.right);
    tmp.best=max(l.right+r.left,max(l.best,r.best));
    return tmp;
}
node build(ll ss,ll se,ll index)
{
    if(ss==se)
    {
        tree[index].sum=tree[index].best=tree[index].left=tree[index].right=arr[ss];
        return tree[index];
    }
    ll mid=(ss+se)/2;
    node l=build(ss,mid,2*index+1);
    node r=build(mid+1,se,2*index+2);
    tree[index]=combine(l,r);
    return tree[index];
}
node query(ll ss,ll se,ll qs,ll qe,ll index)
{
    if(ss==qs && se==qe)
        return tree[index];
    ll mid=(ss+se)/2;
    if(qe<=mid)
        return query(ss,mid,qs,qe,2*index+1);
    if(qs>mid)
        return query(mid+1,se,qs,qe,2*index+2);
    node l=query(ss,mid,qs,mid,2*index+1);           //note: qe replaced by mid
    node r=query(mid+1,se,mid+1,qe,2*index+2);         //note: qs replaced by mid+1
    return combine(l,r);
}
int main()
{
ll i,j,k,l,n,m,t,T,f,p,ans,cnt,par,a,b;
char x;
s(n);
FOR(n)
    s(arr[i]);
build(0,n-1,0);
s(m);
while(m--)
{
    s(a);
    s(b);
    a--;
    b--;
    printf("%lld\n",query(0,n-1,a,b,0).best);
}

return 0;
}


