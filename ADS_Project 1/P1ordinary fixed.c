#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Filename "1.in"

struct XaxisRecord;
struct Node;
typedef struct XaxisRecord *Region;
typedef struct Node *Point;

int Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R);
void Insert(int X, int Y, int N, Region R);
Region Initialize(Region R, int Capacity); 

struct XaxisRecord
{
	int Capacity;
	Point Yaxis[20001];
	//Point *Yaxis;
};

struct Node
{
	int Element;
	int Y;
	struct Node *Next;
};

int Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R)
{
	int i;
	int Count=0;
	Point P;
	for(i=Xmin;i<=Xmax;i++)
	{
		P=R->Yaxis[i];
		while(P!=NULL)
		{
			if(P->Y>=Ymin&&P->Y<=Ymax)
			 Count+=P->Element;
		    if(P->Next->Next->Y)
				i=i;
			  P=P->Next;
		}
	}
	return Count;
	
}

void Insert(int X, int Y, int N, Region R)
{   
    Point Tmp,Tmp1;
    Tmp=(struct Node *)malloc(sizeof(struct Node));
    Tmp->Y=Y;
    Tmp->Element=N;
    Tmp->Next=NULL;
	if(Y==35) 
		Y=35;
	if(R->Yaxis[X]==NULL)
	  R->Yaxis[X]=Tmp;
	else
	{
	  Tmp1=R->Yaxis[X];
	  R->Yaxis[X]=Tmp;
	  Tmp->Next=Tmp1;
	}
	return;
}

Region 
Initialize(Region R, int Capacity)
{   
    int i;
	R=(struct XaxisRecord*)malloc(sizeof(struct XaxisRecord));
	if(R==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	if(R->Yaxis==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	for(i=0;i<Capacity+1;i++)
	  R->Yaxis[i]=NULL;

	return R;
}
Region R;
int main(void)
{
	int i;
	int X=0,Y=0,N=0;
	int Xmin,Xmax,Ymin,Ymax,sum;
	char *ch;
	clock_t start, finish; ///////////////////////////
	int s,t;/////////////////////////
	double time=0;////////////////////
	ch=(char*)malloc(sizeof(char)*5);
    R=Initialize(R,20000);
    if(freopen(Filename,"r",stdin)==NULL)
		exit(0);
    scanf("%s",ch); 
    while(1)
    {
      if(*ch=='I')
      {
	   while(1)
	   {
    	scanf("%s",ch);
    	if(*ch=='Q'||*ch=='E')
    	break;
    	else 
    	{   X=0;
    		while(*ch!=0)
    		{
    			X=X*10+*ch-'0';
    			ch++;
    		}
    		scanf("%d %d",&Y,&N);
			if(Y==76) 
				Y=76;
    		Insert(X,Y,N,R);
    	}
       }
      }
      else if(*ch=='Q')
      {
       while(1)
	   {
    	scanf("%s", ch);
    	if(*ch=='I'||*ch=='E')
    	break;
    	else
    	{   
			Xmin=0;
    		while(*ch!=0)
    		{
    			Xmin=Xmin*10+*ch-'0';
    			ch++;
    		}
    		scanf("%d %d %d",&Xmax,&Ymin,&Ymax);
			for(t=0;t<5;t++){
			start=clock();/////////////////////
			for(s=0;s<10;s++)//////////////////////
    	        sum = Find(Xmin,Xmax,Ymin,Ymax,R);
			finish=clock();////////////////////
			printf("%d\n",sum);
			time = (double)(finish-start);
			printf("time=%lf\n", time);
			}
    	}
       }
      }
      else break;
    }
	system("pause");
}

