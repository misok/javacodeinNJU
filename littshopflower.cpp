#include <stdio.h>
#include <time.h>

int a[100][100];
int b[100][100];

int max(int a,int b){
	return a>b?a:b;
}

 int main()
{
	/* code */
	int F,V;
	int i,j,k;

	while(scanf("%d%d", &F,&V)!= EOF){
		for ( i = 1; i <= F; ++i)
		{
			/* code */
			for ( j = 1; j <= V; ++j)
			{
				/* code */
				scanf("%d",&a[i][j]);
			}
		}
		b[1][1]=a[1][1];
		for ( k = 2; k <= V; ++k)
		{
			/* code */
			b[1][k] = max(a[1][k],b[1][k -1]);

		}
		for(i=2;i<=F;i++){
			b[i][i]=b[i-1][i-1] + a[i][i];
			for(j=i;j<=V;j++){
				b[i][j]=max(b[i-1][j-1])+a[i][j],b[i][j-1];
			}
		}
		printf("%d\n",b[F][V] );
	}
	return 0;
}