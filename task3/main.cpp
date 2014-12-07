//
//  main.cpp
//  task3
//
//  Created by misok on 14-11-1.
//  Copyright (c) 2014年 misok. All rights reserved.
//利用树上的倍增就可以搞定。每个节点都保存它的第2^i的父亲。对于DIST询问，只要利用倍增求出lca，然后减一减就好了。对于KTH询问，先求出lca，然后判断是第一个点到lca的路径上还是第二个点到lca的路径上。//


#include <stdio.h>
#include <string.h>
#include <vector>
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;

const int N=200005;
int n,eid;
int head[N],ed[N<<1],val[N<<1],nxt[N<<1];
vector<int>fa[N];
int sta[N],top,dep[N],dis[N];

void addedge(int s,int e,int v){
    ed[eid]=e;val[eid]=v;nxt[eid]=head[s];head[s]=eid++;
}

void dfs(int s,int f,int d,int ds){
    fa[s].clear();int k=1;dep[s]=d;dis[s]=ds;
    while(top-k>=0){
        fa[s].push_back(sta[top-k]);k*=2;
    }
    sta[top++]=s;
    for(int i=head[s];~i;i=nxt[i]){
        int e=ed[i],v=val[i];
        if(e!=f)dfs(e,s,d+1,ds+v);
    }
    top--;
}

int lca(int a,int b){
    if(a==b)return a;
    if(dep[b]>dep[a])swap(a,b);
    while(dep[a]>dep[b]){
        int len=fa[a].size(),le=0,ri=len,mid;
        while(mid=(le+ri)>>1,ri>le){
            if(dep[fa[a][mid]]>=dep[b])le=mid+1;
            else ri=mid;
        }
        a=fa[a][ri-1];
    }
    if(a==b)return a;
    while(1){
        int len=fa[a].size(),le=0,ri=len,mid;
        while(mid=(le+ri)>>1,ri>le){
            if(fa[a][mid]!=fa[b][mid])le=mid+1;
            else ri=mid;
        }
        if(ri==0)return fa[a][ri];
        a=fa[a][ri-1];b=fa[b][ri-1];
    }
    return a;
}

int kth(int a,int b,int k){
    int r=lca(a,b);
    if(dep[a]-dep[r]+1>=k){
        int u=dep[a]-k+1;
        while(1){
            if(u==dep[a])return a;
            int len=fa[a].size(),le=0,ri=len,mid;
            while(mid=(le+ri)>>1,ri>le){
                if(dep[fa[a][mid]]>=u)le=mid+1;
                else ri=mid;
            }
            a=fa[a][ri-1];
        }
    }
    else{
        int u=k-dep[a]+dep[r]*2-1;
        while(1){
            if(u==dep[b])return b;
            int len=fa[b].size(),le=0,ri=len,mid;
            while(mid=(le+ri)>>1,ri>le){
                if(dep[fa[b][mid]]>=u)le=mid+1;
                else ri=mid;
            }
            b=fa[b][ri-1];
        }
    }
}

int main(){
    //    freopen("/home/axorb/in","r",stdin);
    int T;scanf("%d",&T);
    while(T--){
        eid=0;clr(head,-1);scanf("%d",&n);
        for(int i=1;i<n;i++){
            int a,b,c;scanf("%d%d%d",&a,&b,&c);
            addedge(a,b,c);addedge(b,a,c);
        }
        top=0;dfs(1,-1,1,0);
        //        for(int i=1;i<=n;i++)printf("%d %d %d\n",i,fa[i].size(),dep[i]);
        char ss[20];
        while(scanf("%s",ss),ss[1]!='O')
            if(ss[1]=='I'){
                int a,b;scanf("%d%d",&a,&b);
                int r=lca(a,b);
                printf("%d\n",dis[a]+dis[b]-2*dis[r]);
            }
            else{
                int a,b,c;scanf("%d%d%d",&a,&b,&c);
                printf("%d\n",kth(a,b,c));
            }
        puts("");
    }
}