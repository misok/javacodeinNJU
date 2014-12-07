//
//  main.cpp
//  task4
//
//  Created by misok on 14-11-11.
//  Copyright (c) 2014年 misok. All rights reserved.
//  需要使用双层bfs  先bfs”推“，在没推一次时bfs”走".

# include<iostream>
# include<cstring>
# include<string>
using namespace std;
struct node
{
    int sx,sy,bx,by;
    string ans;
} lxk[2][1000005];
int r,c,via[][2]={-1,0,1,0,0,-1,0,1};//注意题目要求的是n、s、w、e的顺序，因为这个wa了一次
char op[]={'n','s','w','e'};
char box[25][25];
char up(char c)
{
    return (c-'a'+'A');
}
bool bfs(int tx,int ty,node &cc)//对走的过程bfs，搜索从推上一步到当前推箱子的前一格
{
    if (tx<=0||tx>r||ty<=0||ty>c||box[tx][ty]=='#') return false;
    bool mark[25][25];
    memset(mark,false,sizeof(mark));
    lxk[1][1]=cc;
    int st,en;
    st=1; en=1;
    node a,b;
    bool p=false;
    while (st<=en)
    {
        a=lxk[1][st];
        if (a.sx==tx&&a.sy==ty)
        {
            p=true;
            cc=a;
            break;
        }
        for (int i=0;i<4;i++)
        {
            int x,y;
            x=a.sx+via[i][0]; y=a.sy+via[i][1];
            if (x>0&&x<=r&&y>0&&y<=c&&!(x==a.bx&&y==a.by)&&!mark[x][y]&&box[x][y]!='#')
            {
                b=a;
                b.sx=x; b.sy=y;
                b.ans=b.ans+op[i];
                mark[x][y]=true;
                en++;
                lxk[1][en]=b;
            }
        }
        st++;
    }
    return p;
}
int main()
{
    int i,j,tx,ty,ca=1;
    while (~scanf("%d%d",&r,&c))
    {
        if (!r||!c) break;
        for (i=1;i<=r;i++)
        {
            getchar();
            for (j=1;j<=c;j++)
            {
                scanf("%c",&box[i][j]);
                if (box[i][j]=='T')
                {
                    tx=i; ty=j;
                    box[i][j]='.';
                }
                if (box[i][j]=='S')
                {
                    lxk[0][1].sx=i; lxk[0][1].sy=j;
                    box[i][j]='.';
                }
                if (box[i][j]=='B')
                {
                    lxk[0][1].bx=i; lxk[0][1].by=j;
                    box[i][j]='.';
                }
            }
        }
        lxk[0][1].ans="";
        int st,en;
        st=1; en=1;
        node a,b;
        bool p=false;
        bool mark[25][25][4];
        memset(mark,false,sizeof(mark));
        string ans;
        printf("Maze #%d\n",ca++);
        while (st<=en)//对推的过程bfs
        {
            a=lxk[0][st];
            if (a.bx==tx&&a.by==ty)
            {
                p=true;
                ans=a.ans;
                break;
            }
            for (i=0;i<4;i++)
            {
                int x,y;
                x=a.bx+via[i][0]; y=a.by+via[i][1];
                if (x>0&&x<=r&&y>0&&y<=c&&!mark[x][y][i]&&box[x][y]!='#')
                {
                    b=a;
                    if (bfs(x-2*via[i][0],y-2*via[i][1],b))
                    {
                        b.sx=b.bx; b.sy=b.by;
                        b.bx=x; b.by=y;
                        b.ans=b.ans+up(op[i]);
                        mark[x][y][i]=true;
                        en++;
                        lxk[0][en]=b;
                    }
                }
            }
            st++;
        }
        if (p) printf("%s\n\n",ans.c_str());
        else printf("Impossible.\n\n");
    }
    return 0;
}
