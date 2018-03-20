#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h" 
#include "windows.h"

#define INF 65535 


LARGE_INTEGER nFreq;//cpu frequency  
LARGE_INTEGER t1;//begin
LARGE_INTEGER t2;//end
double dt[6]; //time

int arr[6] = {8,16,32,64,128,256};
int count;

FILE *fp;


typedef struct ENode 
{  
    int u = 0; 
    int v = 0; 
    ENode *next = NULL;  
    int w = INF; 
}ENode;  
    
typedef struct VNode
{  
    int id = 0; 
    ENode *first = NULL;
    int key = INF; 
                         
    int parent = 0;
	int d = INF;       
    int indegree = 0;        
}VNode; 

void FileWritePathOutput1(void)
{
	switch (count)
		{
			case 0:fp = fopen("../output/size1/output1.txt","a");break;
			case 1:fp = fopen("../output/size2/output1.txt","a");break;
			case 2:fp = fopen("../output/size3/output1.txt","a");break;
			case 3:fp = fopen("../output/size4/output1.txt","a");break;
			case 4:fp = fopen("../output/size5/output1.txt","a");break;
			case 5:fp = fopen("../output/size6/output1.txt","a");break;
		}
}

void FileWritePathTime1(void)
{
	switch (count)
		{
			case 0:fp = fopen("../output/size1/time1.txt","a");break;
			case 1:fp = fopen("../output/size2/time1.txt","a");break;
			case 2:fp = fopen("../output/size3/time1.txt","a");break;
			case 3:fp = fopen("../output/size4/time1.txt","a");break;
			case 4:fp = fopen("../output/size5/time1.txt","a");break;
			case 5:fp = fopen("../output/size6/time1.txt","a");break;
		}
}

void FileWritePathOutput2(void)
{
	switch (count)
		{
			case 0:fp = fopen("../output/size1/output2.txt","a");break;
			case 1:fp = fopen("../output/size2/output2.txt","a");break;
			case 2:fp = fopen("../output/size3/output2.txt","a");break;
			case 3:fp = fopen("../output/size4/output2.txt","a");break;
			case 4:fp = fopen("../output/size5/output2.txt","a");break;
			case 5:fp = fopen("../output/size6/output2.txt","a");break;
		}
}

void FileWritePathTime2(void)
{
	switch (count)
		{
			case 0:fp = fopen("../output/size1/time2.txt","a");break;
			case 1:fp = fopen("../output/size2/time2.txt","a");break;
			case 2:fp = fopen("../output/size3/time2.txt","a");break;
			case 3:fp = fopen("../output/size4/time2.txt","a");break;
			case 4:fp = fopen("../output/size5/time2.txt","a");break;
			case 5:fp = fopen("../output/size6/time2.txt","a");break;
		}
}


void printd(VNode *G,int n)
{
		printf("\n\n");
		
		for(int i = 1;i <= n+1;i++)
		    printf("%d  %d\n",i,G[i].d);
}


void printw(VNode *G,int n)
{
	printf("\n\n");
		
		for(int i = 1;i <= n;i++)
		{
			ENode *q = G[i].first;
			printf("%d  ",i);
			while(q)
			{
				printf("%d ",q->w);
				q = q -> next;
			}
			printf("\n");
		}
}

void fprint_shortest_path(VNode *G,int v)
{
	if(v == 0)
		return;
	fprint_shortest_path(G,G[v].parent);
	fprintf(fp,"%d ",v);
}


void Random_Num(void)
{
	int m,n;
	srand((unsigned)time(NULL));
	for(count = 0;count < 6;count++)
	{
		int k = 0;
		n = arr[count];//v
		int G[n+1][n+1];
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
				G[i][j] = INF;
		}
 		m = n*log2(n);//G
		switch (count)
		{
			case 0:fp = fopen("../input/size1/input.txt","w");break;
			case 1:fp = fopen("../input/size2/input.txt","w");break;
			case 2:fp = fopen("../input/size3/input.txt","w");break;
			case 3:fp = fopen("../input/size4/input.txt","w");break;
			case 4:fp = fopen("../input/size5/input.txt","w");break;
			case 5:fp = fopen("../input/size6/input.txt","w");break;
		}
		while(1)
		{
			int r1 = 1+rand()%n;
			int r2 = 1+rand()%n;
			if(G[r1][r2] == INF)
			{
				if(rand()%n == 1)
				{
					G[r1][r2] = - (1 + rand()%((int)log2(n)));
				}
				else
					G[r1][r2] = 1 + rand()%n;
			
				fprintf(fp,"%d ",r1);
				fprintf(fp,"%d ",r2);
				fprintf(fp,"%d\n",G[r1][r2]);
				k++;
			}
			if(k == m)
				break;
		}
		if(k < m)
			printf("less than nlogn!");
	 	fclose(fp);
	}
}

INITIALZE_SINGLE_SOURCE(VNode *G,int s,int n)
{
	for(int i = 1;i <= n;i++)
	{
		G[i].d = INF;
		G[i].parent = 0;
	}
	G[s].d = 0;	
}

void RELAX(VNode *G,int u,int v,int w)
{
	if(G[v].d > (G[u].d + w))
	{
		G[v].d = G[u].d + w;
		G[v].parent = u;
	}
}


int Bellman_Ford(VNode *G,int s,int n)
{
	INITIALZE_SINGLE_SOURCE(G,s,n);
	for(int i = 1;i < n;i++)
	{
		for(int j = 1;j <= n;j++)
		{
			ENode *q = G[j].first;
			while(q)
			{
				RELAX(G,q->u,q->v,q->w);
				q = q -> next;
			}
		}
	}
	for(int i = 1;i <= n;i++)
	{
		ENode *q = G[i].first;
		while(q)
		{
			if(G[q->v].d > (G[q->u].d + q->w))
				return 0;
			q = q -> next;
		}
	}
	return 1;	
}

/*
void MIN_HEAPIFY(int *a,int i,int n)
{
	int l = 2*i;
	int r = 2*i + 1;
	int min = 0;
	if(l <= n && a[l] < a[i])
		min = l;
		else
		min = i;
	if(r <= n && a[r] < a[min])
		min = r;
	if(min != i)
	{
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		MIN_HEAPIFY(a,min,n);
	}
}

BUILD_MIN_HEAP(int *a,int n)
{
	for(int i = floor(n);i >= 1;i--)
		MIN_HEAPIFY(a,i,n);
}

int HEAP_EXTRACT_MIN(int *a,int n)
{
	int min = a[1];
	a[1] = a[n];
	n--;
	MIN_HEAPIFY(a,1,n);
	return min;
}*/

void Dijkstra(VNode *G,int s)
{
	int n = arr[count];
	INITIALZE_SINGLE_SOURCE(G,s,n);
	int u;
	int *Q[n+1];
	memset(Q,INF,sizeof(Q));
	for(int i = 1;i <= n;i++)
		Q[i] = &G[i].d;	
	while(n)
	{
		int min = INF;
		for(int i = 1;i <= arr[count];i++)
		{
			if(Q[i] == NULL)
				continue;
			if(*Q[i] < min)
			{
				min = *Q[i];
				u = i;
			}		
		}
		Q[u] = NULL;
		n--;
		ENode *q = G[u].first;
		while(q)
		{
			RELAX(G,q->u,q->v,q->w);
			q = q->next;
		}
	}
}


void JohnSon(VNode *G,int n)
{
	QueryPerformanceCounter(&t1);
	int h[n+1];
	memset(h,0,sizeof(h));
	int D[n+1][n+1];
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= n;j++)
			D[i][j] = INF;
	}
	int s = n + 1;
	G[s].d = 0;
	ENode E[n+1];
	G[s].first = &E[1];
	for(int i = 1;i <= n;i++)
	{
		E[i].u = n+1;
		E[i].v = i;
		E[i].w = 0;
		if(i == n)
			break;
		E[i].next = &E[i+1];
	}
	if(!(Bellman_Ford(G,s,n+1)))
		printf("the input graph contains a negative-weight cycle\n");
	else
	{	
	//	printd(G,n);	    
	//	printw(G,n);
		for(int i = 1;i <= n;i++)
			h[i] = G[i].d;
		for(int j = 1;j <= n;j++)
		{
			ENode *q = G[j].first;
			while(q)
			{
				q->w = q->w + h[q->u] - h[q->v];;
				q = q -> next;
			}	
		}	
		//	printd(G,n);
		//	printw(G,n);
		FileWritePathOutput2();	
		for(int i = 1;i <= n;i++)
		{
			Dijkstra(G,i);
		//	printd(G,n);
		//	printw(G,n);	
			for(int k = 1;k <= n;k++)
			{
				D[i][k] = G[k].d + h[k] - h[i];
				if(D[i][k] == INF)
				{
					fprintf(fp,"%d ",i);
					fprintf(fp,"%d ",k);
					fprintf(fp,"Length: %c\n",'$');
				}
				else
				{
					fprint_shortest_path(G,k);
					fprintf(fp,"Length: %2d\n",D[i][k]);
				}
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
	QueryPerformanceCounter(&t2);
	FileWritePathTime2();
	fprintf(fp,"%f\n",(t2.QuadPart - t1.QuadPart)/ (double)nFreq.QuadPart *1000000);
	fclose(fp);
}




int main()
{
//	Random_Num(); 
	int i,j;
	QueryPerformanceFrequency(&nFreq);
	for(count = 0;count < 6;count++)
	{
	 	int m = 0,n = 0,k = 1;
		n = arr[count];//v
		int G[n+1][n+1];
		VNode V[n+2];
		ENode *p[n+1];
		m = n*log2(n);//e
		int v1[m+1],v2[m+1];
		
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
				G[i][j] = INF;
		}
		memset(v1,0,sizeof(v1));
		memset(v2,0,sizeof(v2));
		
		switch (count)
		{
			case 0:fp = fopen("../input/size1/input.txt","r");break;
			case 1:fp = fopen("../input/size2/input.txt","r");break;
			case 2:fp = fopen("../input/size3/input.txt","r");break;
			case 3:fp = fopen("../input/size4/input.txt","r");break;
			case 4:fp = fopen("../input/size5/input.txt","r");break;
			case 5:fp = fopen("../input/size6/input.txt","r");break;
		}
		
		char line[31];
		char ch[1];
		memset(line,NULL,sizeof(line));
		while(fgets(line,31,fp))
		{
			int i = 0;
			int Nflag = 0;
			int num = 0;
			while (line[i] >= '0' && line[i] <= '9')
			{
				num = num * 10 + line[i] - '0';
				++i;
			} 
			
			v1[k] = num;
			
			++i;
			num = 0;
			while (line[i] >= '0' && line[i] <= '9')
			{
				num = num * 10 + line[i] - '0';
				++i;
			} 
			
			v2[k] = num;
			
			++i;
			num = 0;
			if(line[i] == '-')
			{
				++i; 
				Nflag = 1;
			}
			while (line[i] >= '0' && line[i] <= '9')
			{
				num = num * 10 + line[i] - '0';
				++i;
			}
			
			if(Nflag == 1)
				G[v1[k]][v2[k]] = -num;
				else
				G[v1[k]][v2[k]] = num;
			
			ENode *e = new ENode;
			
			e->w = G[v1[k]][v2[k]];
			e->u = v1[k];
			e->v = v2[k];
			
			if(!V[v1[k]].first)
			{
				V[v1[k]].id = v1[k];
				V[v1[k]].first = e;
				V[v1[k]].indegree++;
				p[v1[k]] = e;
			}
			else
			{
				p[v1[k]]->next = e;
				p[v1[k]] = p[v1[k]]->next;
			}

				
			k++;
			if(k == m + 1)
				break;
		}		
/*		for(i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				if(G[i][j] == INF)
					printf("%2c ",'$');
				else
					printf("%2d ",G[i][j]);
			}
			printf("\n");
		}*/
//		printf("\n\n");
		
//		printw(V,n);
		
//		Dijkstra(V,1);
//		printf("%d",Bellman_Ford(V,1,n));
		JohnSon(V,n);		
//		printd(V,n);
		printf("n = %d completed!\n\n",n);	
	}
	

	
	 
	 return 0;
}

