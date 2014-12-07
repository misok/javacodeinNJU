import java.util.*;

class edge{
	int b;
	int e;
	edge(){
		b=0;
		e=0;
	}
}
public class RevolutionaryRoad {
 int max=2000;
 edge E[]=new edge[20000];
 int n,m,res=0,resnum;
 int DFN[]=new int[max];
 int LOW[]=new int[max];
 int Stap[]=new int[max];
 int Belong[]=new int[max];
 int Bnum[]=new int[max];
 boolean instack[]=new boolean[max];
 Vector<Integer> po[]=new Vector[max];
 Vector<Integer> TT[]=new Vector[max];
 int Dindex,Stop,Bcnt;
 int to[][]=new int[max][max];
 int mark[]=new int[20000];
 int ans[]=new int[20000];
 int vi[]=new int[max];
 int I;
 
 RevolutionaryRoad(){
	 for(int i=0;i<max;i++){
		 po[i]=new Vector();
		 TT[i]=new Vector();
	 }
	 for(int i=0;i<20000;i++)
		 E[i]=new edge();
 }
 void tarjan(int i){
	 int j;
	 DFN[i]=LOW[i]=++Dindex;
	 instack[i]=true;
	 Stap[++Stop]=i;
	 for(int b=0;b<po[i].size();b++){
		 j=po[i].get(b);
		 if(DFN[j]==0){
			 tarjan(j);
			 if(LOW[j]<LOW[i])
				 LOW[i]=LOW[j];
		 }
		 else if(instack[j]&&DFN[j]<LOW[i])
		 LOW[i]=DFN[j];
	 }
	 if(DFN[i]==LOW[i]){
		 Bcnt++;
		 do{
			 j=Stap[Stop--];
			 instack[j]=false;
			 Belong[j]=Bcnt;
			 Bnum[Bcnt]++;
		 }while(j!=i);
	 if(res<Bnum[Bcnt]){
		 res=Bnum[Bcnt];
		 resnum=Bcnt;
	 }
	}
 }
 
 void solve(){
	 int i;
	 Stop=Bcnt=Dindex=0;
	 for(i=0;i<max;i++)
		 DFN[i]=0;
	 for(i=1;i<=n;i++)
		 if(DFN[i]==0)
			 tarjan(i);
 }
 
 void dfs(int start,int fa){
	 int k;
	 vi[start]=1;
	 int size=TT[start].size();
	 for(k=0;k<size;k++){
		 int v=TT[start].get(k);
		 if(v!=fa&&vi[v]==0){
			 to[I][v]=1;
			 vi[v]=1;
			 dfs(v,start);
		 }
	 }
	 return ;
 }
 
 void init(){
	res=0;
	resnum=0;
 }
 
 public static void main(String[] args){
	 RevolutionaryRoad rr=new RevolutionaryRoad();
	 Scanner in=new Scanner(System.in);
	 while(in!=null){
	   rr.n=in.nextInt();
	   rr.m=in.nextInt();
	   rr.init();
	   int be,en;
	   for(int i=1;i<=rr.m;i++){
		   be=in.nextInt();
		   en=in.nextInt();
		   //rr.po[be]=new Vector();
		   rr.po[be].addElement(en);
		   //rr.E[i]=new edge();
		   rr.E[i].b=be;
		   rr.E[i].e=en;
	   }
	   rr.solve();
	   int i,j;
	   for(i=1;i<=rr.m;i++){
		if(rr.Belong[rr.E[i].b]!=rr.Belong[rr.E[i].e]){
			//rr.TT[rr.Belong[rr.E[i].b]]=new Vector();
			rr.TT[rr.Belong[rr.E[i].b]].addElement(rr.Belong[rr.E[i].e]);
		}
	   }
	   for(rr.I=1;rr.I<=rr.Bcnt;rr.I++){
		   for(i=0;i<rr.max;i++)
			   rr.vi[i]=0;
		   rr.dfs(rr.I, -1);
	   }
	   int ma=rr.res;
	   int cnt=0;
	   
	   for(i=1;i<=rr.m;i++)  
	    {  
	        if(rr.Belong[rr.E[i].b]!=rr.Belong[rr.E[i].e])  
	        {  
	            cnt=rr.Bnum[rr.Belong[rr.E[i].b]]+rr.Bnum[rr.Belong[rr.E[i].e]];
	            for(j=1;j<=rr.Bcnt;j++)  { 
	              if(rr.to[rr.Belong[rr.E[i].b]][j]==1 && rr.to[j][rr.Belong[rr.E[i].e]]==1 && j!=rr.Belong[rr.E[i].e]) 
	                     cnt+=rr.Bnum[j];  
	            }  
	           rr.mark[i]=cnt;  
               if(cnt>ma)  
               {  
                ma=cnt;
                cnt=0;  
               }  
	        }
        }   
	 int total=0;  
     if(ma==rr.res)  
     {  
        for(j=1;j<=rr.m;j++)  
        {  
          if(rr.Belong[rr.E[j].b]==rr.Belong[rr.E[j].e] && rr.Bnum[rr.Belong[rr.E[j].b]]==rr.res||rr.mark[j]==rr.res)  
                    rr.ans[total++]=j;  
        }  
     }  
     else  
     {  
        for(j=1;j<=rr.m;j++)  
           {  
               if(rr.mark[j]==ma)  
               rr.ans[total++]=j;  
           }  
     }  
     System.out.println(ma);
     System.out.println(total);
  
     {  
         if(total==0)  
         System.out.println();  
         else  
         {  
             for(i=0;i<total-1;i++)  
             {  
                System.out.print(rr.ans[i]+" ");  
             }  
           System.out.print(rr.ans[total-1]+" ");  
         }  
  
     }  
    }  
    return ;      
	 
	 
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
}



