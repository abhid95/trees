#include <bits/stdc++.h>
#define MAX 1000000007
#define pb push_back
#define mp make_pair
#define FOR(n) for(i=0;i<n;i++)
#define rep(i,n) for(i=0;i<n;i++)
#define reps(i,a,b) for(i=a;i<=b;i++)
#define ll long long int
#define que queue<int>
#define s(t) scanf("%d",&t)
#define p(t) printf("%d\n",t)
using namespace std;

ll lazy[1000000];
ll getsum(ll st[],ll qs,ll qe,ll ss,ll se,ll index)
{
    ll mid=ss+(se-ss)/2;
    if(lazy[index]!=0)
    {
        st[index]+=lazy[index];
        if(ss!=se)
        {
            lazy[index*2+1]=lazy[index*2+1]+lazy[index]/2;
            lazy[index*2+2]=lazy[index*2+2]+lazy[index]/2;
        }
        lazy[index]=0;
    }
    if(ss>=qs && se<=qe)
        return st[index];
    if(ss>qe || se<qs)
        return 0;

    return getsum(st,qs,qe,ss,mid,2*index+1)+getsum(st,qs,qe,mid+1,se,2*index+2);

}
void update(ll st[],ll ss,ll se,ll qs,ll qe,ll add,ll index)
{

    ll mid=ss+(se-ss)/2;
    if(lazy[index]!=0)
    {
        st[index]+=lazy[index];
        if(ss!=se)
        {
            lazy[index*2+1]=lazy[index*2+1]+lazy[index]/2;
            lazy[index*2+2]=lazy[index*2+2]+lazy[index]/2;
        }
        lazy[index]=0;
    }
    if(qe<ss || qs>se || ss>se)
        return;
    if(ss>=qs && se<=qe)
    {
        st[index]+=add*(se-ss+1);
        if(ss!=se)
        {
            lazy[index*2+1]=lazy[index*2+1]+add*(mid-ss+1);
            lazy[index*2+2]=lazy[index*2+2]+add*(se-mid);

        }
        return;
    }

    update(st,ss,mid,qs,qe,add,2*index+1);
    update(st,mid+1,se,qs,qe,add,2*index+2);
    st[index]=st[index*2+1]+st[index*2+2];//+(mid-ss+1)*lazy[2*index+1]+(se-mid)*lazy[2*index+2];

}
ll st[1000000];
int main()
{
ll i,j,k,l,n,m,t,f,p,ans,cnt,qs,qe,ss,se,arr[100005],opt,q,add;
char x;
cin>>t;
while(t--)
{
    memset(st,0,sizeof(st));
    memset(lazy,0,sizeof(lazy));
    cin>>n>>q;
    while(q--)
    {
        cin>>opt;
        if(opt)
        {
            cin>>qs>>qe;
            qs--;
            qe--;
            ans=getsum(st,qs,qe,0,n-1,0);
            cout<<ans<<endl;
        }
        else
        {
            cin>>qs>>qe>>add;
            qs--;
            qe--;
            //cout<<qs<<" "<<qe<<" "<<add<<endl;
            update(st,0,n-1,qs,qe,add,0);
        }
       /*
        FOR(20)

            cout<<" "<<st[i]<<"("<<i<<")";
        cout<<endl;
        FOR(20)
            cout<<" "<<lazy[i]<<"("<<i<<")";
        cout<<endl;*/



    }
}

return 0;
}


