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
#define s(t) scanf("%d",&t)
#define p(t) printf("%d\n",t)
using namespace std;
int bit[100005];
struct node
{
    int val,ind,l,r;
    bool t;
};
bool operator<(node a,node b)
{
    if(a.r==b.r)
        return a.t<b.t;
    return a.r<b.r;
}
void add(int y,int val)
{
    while(y<=30000)
    {
        bit[y]+=val;
        y+=(y & -y);
    }
}
int sum(int y)
{
    int res=0;
    while(y>0)
    {
        res+=bit[y];
        y-=(y & -y);
    }
    return res;
}
node a[230000];
int prev[1000006],ans[200005];
bool vis[1000006];
int main()
{
int i,j,k,l,n,m,t,T,f,p,cnt,par,ele,q;
char x;
memset(vis,0,sizeof vis);
memset(prev,0,sizeof prev);
s(n);
for(i=1;i<=n;i++)
{
    add(i,1);
}
for(i=0;i<n;i++)
{
    scanf("%d",&a[i].val);
    a[i].t=0;
    a[i].ind=i+1;
    a[i].r=i+1;
}
s(q);
for(i=n;i<n+q;i++)
{
    scanf("%d%d",&a[i].l,&a[i].r);
    a[i].ind=i-n;
    a[i].t=1;
}
sort(a,a+n+q);
for(i=0;i<n+q;i++)
{
    if(a[i].t)
    {
        ans[a[i].ind]=sum(a[i].r)-sum(a[i].l-1);
    }
    else
    {
        if(vis[a[i].val])
            if(prev[a[i].val]!=0)
                add(prev[a[i].val],-1);
        vis[a[i].val]=1;
        prev[a[i].val]=a[i].ind;
    }
}
FOR(q)
{
    printf("%d\n",ans[i]);
}



return 0;
}



