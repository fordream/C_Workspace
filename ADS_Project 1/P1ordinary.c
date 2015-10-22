#include<stdio.h>
#include<stdlib.h>
#define Filename "1.in"

struct XaxisRecord;
struct Node;
typedef struct XaxisRecord *Region;
typedef struct Node *Point;

void Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R);
void Insert(int X, int Y, int N, Region R);
Region Initialize(Region R, int Capacity); 

struct XaxisRecord
{
	int Capacity;
	Point *Yaxis; 
};

struct Node
{
	int Element;
	int Y;
	struct Node *Next;
};

void Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R)
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
			 P=P->Next;
		}
	}
	
	printf("%d\n", Count);
}

void Insert(int X, int Y, int N, Region R)
{   
    Point Tmp,Tmp1;
    Tmp=malloc(sizeof(struct Node));
    if(Tmp==NULL)
    {
    	printf("Fuck it");
    	exit(0);
    }
    Tmp->Y=Y;
    Tmp->Element=N;
    Tmp->Next=NULL;
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
	R=malloc(sizeof(struct XaxisRecord));
	if(R==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	R->Yaxis=malloc(sizeof(Point)*(Capacity+1));
	if(R->Yaxis==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	for(i=1;i<Capacity+1;i++)
	 R->Yaxis[i]=NULL;
	 
	return R;
}

int main(void)
{
	Region R;
	int i;
	int X=0,Y=0,N=0;
	int Xmin,Xmax,Ymin,Ymax;
	char *ch;
	
	ch=malloc(sizeof(char)*5);
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
    	{   Xmin=0;
    		while(*ch!=0)
    		{
    			Xmin=Xmin*10+*ch-'0';
    			ch++;
    		}
    		scanf("%d %d %d",&Xmax,&Ymin,&Ymax);
    	    Find(Xmin,Xmax,Ymin,Ymax,R);
    	}
       }
      }
      else break;
    }

}

