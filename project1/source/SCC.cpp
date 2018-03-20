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
int t;

FILE *fp;


enum color
{
	WHITE,
	GRAY,
	BLACK
};

typedef struct GNode
{
	int id;
	int color = WHITE;
	int d;
	int f;
	struct GNode *Node = NULL;
	struct GNode *parent = NULL;
	struct GNode *next = NULL;
}GNode,*Graph;

const Graph NIL = new GNode;


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

void Random_Num(void)
{
	int m,n;
	srand((unsigned)time(NULL));
	for(count = 0;count < 6;count++)
	{
		int k = 0;
		n = arr[count];//v
		int e[n+1][n+1];
		memset(e,0,sizeof(e));
		m = n*log2(n);//e
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
			if(e[r1][r2] != 1)
			{
				e[r1][r2] = 1;
				fprintf(fp,"%d ",r1);
				fprintf(fp,"%d\n",r2);
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


DFS_VISIT(GNode *G,int u)
{
	int i,j;
	GNode *p;
	++t;
	G[u].d = t;
	G[u].color = GRAY;
//	printf("%d\n",G[u].f);
	p = G[u].next;
	while(p)
	{
		if(p->Node->color == WHITE)
		{
			p->parent = &G[u];
			p->Node->color = GRAY;
			DFS_VISIT(G,p->Node->id);
		}
		p = p->next;		
	}
	G[u].color = BLACK;
//	printf("%d  ",u);
	t = t + 1;
	G[u].f = t;
//	printf("%d\n",G[u].f);
}


void DFS(GNode *G,int u)
{
	int i,v;
	t = 0;
	for(i = 1;i <= u;i++)
	{
		if(G[i].color == WHITE)
		DFS_VISIT(G,i);
	}
	
}

DFS_VISIT_P(GNode *G,int u)
{
	int i,j;
	GNode *p;
	++t;
	G[u].d = t;
	G[u].color = GRAY;
//	printf("%d\n",G[u].f);
	p = G[u].next;
	while(p)
	{
		if(p->Node->color == WHITE)
		{
			p->parent = &G[u];
			p->Node->color = GRAY;
			DFS_VISIT_P(G,p->Node->id);
		}
		p = p->next;		
	}
	G[u].color = BLACK;
	printf("%d  ",u);
	FileWritePathOutput1();
	fprintf(fp,"%d ",u);
	fclose(fp);
	t = t + 1;
	G[u].f = t;
//	printf("%d\n",G[u].f);
}

void DFS_P(GNode *GT,GNode *G,int u)
{
	int i,j,min,temp,sort[u+1];
	t = 0;
	for(i = 1;i <= u;i++)
		sort[i] = G[i].f;
	for(i = 1;i <= u - 1;i++)
	{
		min = i;
		for(j = i + 1;j <= u;j++)
		{
			if(sort[min] >= sort[j])
			{
				min = j;
			}
		}
		temp = sort[i];
		sort[i] = sort[min];
		sort[min] = temp;
	}						//sort
	for(i = u;i >= 1;i--)
	{	
		j = 1;
		while(j)
		{
			if(G[j].f== sort[i])
				break;
			j++;
		}	
		if(GT[j].color == WHITE)
		{
			QueryPerformanceCounter(&t1);
			DFS_VISIT_P(GT,j);
			QueryPerformanceCounter(&t2);
			printf("\n");
			FileWritePathOutput1();
			fprintf(fp,"\n");
			fclose(fp);
			FileWritePathTime1();
			fprintf(fp,"%f\n",(t2.QuadPart - t1.QuadPart)/ (double)nFreq.QuadPart *1000000);
			fclose(fp);
		}
	}
	
}

STRONGLY_CONNECTED_COMPONENTS(GNode *G,int u,int *e)
{
	int i,j,k = 0;
	GNode GT[u+1];
	GNode *pT[u+1];
	DFS(G,u);
	for(i = 1;i <= u;i++)
		{
			for(j = i;j <= u;j++)
			{
				if(*(e + i*(u+1) + j) == 1 && *(e + j*(u+1) + i) == 0)
				{
					*(e + i*(u+1) + j) = 0;
					*(e + j*(u+1) + i) = 1;
				}
				else if(*(e + i*(u+1) + j) == 0 && *(e + j*(u+1) + i) == 1)
				{
					*(e + i*(u+1) + j) = 1;
					*(e + j*(u+1) + i) = 0;
				}
				
			}
		}
	
	for(i = 1;i <= u;i++)
	{
		for(j = 1;j <= u;j++)
		{
			if(*(e + i*(u+1) + j) == 1)
			{
				Graph v = new GNode;
				GT[j].id = j;
				GT[j].Node = &GT[j];
				v->Node = &GT[j];
				if(!GT[i].next)
				{
					GT[i].id = i;
					GT[i].Node = &G[i];
					GT[i].next = v;	
					pT[i] = v;
				}
				else
				{
					pT[i]->next = v;
					pT[i] = pT[i]->next;
				}
			}
		}
	}
	printf("\n");
/*	for(i = 1;i <= u;i++)
		{
			for(j = 1;j <= u;j++)
				printf("%d ",*(e + i*(u+1) + j));
			printf("\n");
		}*/
	DFS_P(GT,G,u);
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
		int e[n+1][n+1];
		GNode G[n+1];
		GNode *p[n+1];
		m = n*log2(n);//e
		int e1[m+1],e2[m+1];
		memset(e,0,sizeof(e));
		memset(e1,0,sizeof(e1));
		memset(e2,0,sizeof(e1));
		
		
		NIL->id = INF;
		NIL->color = WHITE;
		NIL->next = NULL;
		
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
			int num = 0;
			while (line[i] >= '0' && line[i] <= '9')
			{
				num = num * 10 + line[i] - '0';
				++i;
			} 
			
			e1[k] = num;
			
			++i;
			num = 0;
			while (line[i] >= '0' && line[i] <= '9')
			{
				num = num * 10 + line[i] - '0';
				++i;
			} 
			
			e2[k] = num;
				
			
			e[e1[k]][e2[k]] = 1;
			
			Graph v = new GNode;
			G[e2[k]].id = e2[k];
			G[e2[k]].Node = &G[e2[k]];
			v->Node = &G[e2[k]];
			if(!G[e1[k]].next)
			{
				G[e1[k]].id = e1[k];
				G[e1[k]].Node = &G[e1[k]];
				G[e1[k]].next = v;	
				p[e1[k]] = v;
			}
			else
			{
				p[e1[k]]->next = v;
				p[e1[k]] = p[e1[k]]->next;
			}	
			k++;
			if(k == m + 1)
				break;
		}
		
/*		for(i = 1;i <= n;i++)
		{
			for(j = 1;j <= n;j++)
				printf("%d ",e[i][j]);
			printf("\n");
		}*/
		
	STRONGLY_CONNECTED_COMPONENTS(G,n,*e);		

	printf("\n\n");	
	}
	 
	 
	 
	 return 0;
}
