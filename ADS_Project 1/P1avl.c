#include<stdio.h>
#include<stdlib.h>
#define Filename "3.in"
#define End 3
#define Start 2

struct XaxisRecord;
struct AvlNode;
typedef struct AvlNode *Point;
typedef struct AvlNode *AvlTree;
typedef struct XaxisRecord *Region;

Region Initialize(Region R, int Capacity); 
void InsertCoordinate(int X, int Y, int N, Region R);
void Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R);
AvlTree OrdinaryInsert(int X, AvlTree T, int StartOrEnd);
AvlTree FindNode(int X,AvlTree T);
AvlTree Insert(int Y,int N,AvlTree T);
int Max(int X1,int X2);
void Traversal(Region R);
void Tvs(AvlTree T);
int Pretraversal(AvlTree T);
static AvlTree SingleRotateWithLeft(AvlTree K2);
static AvlTree SingleRotateWithRight(AvlTree K2);
static AvlTree DoubleRotateWithLeft(AvlTree K3);
static AvlTree DoubleRotateWithRight(AvlTree K3);

struct XaxisRecord
{
	int Capacity;
	AvlTree *Yaxis; 
};

struct AvlNode
{
	int Element;
	int Y;
	int StartOrEnd;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

static int
Height(AvlTree P)
{
	if(P==NULL)
	  return -1;
	else
	  return P->Height;
}

AvlTree
Insert(int Y, int N, AvlTree T)
{  
	if(T==NULL)
	{
		T=malloc(sizeof(struct AvlNode));
		if(T==NULL)
		{
			printf("Out of space");
			exit(0);
		}
		else
		{
			T->Element=N;
			T->Y=Y;
			T->Height=0;
			T->Left=T->Right=NULL;
		}
	}
	else 
	if(Y<T->Y)
	{
		T->Left=Insert(Y,N,T->Left);
		if(Height(T->Left)-Height(T->Right)==2)
		  if(Y<T->Left->Y)
		    T=SingleRotateWithLeft(T);
	      else
	        T=DoubleRotateWithLeft(T);
	}
	else 
	if(Y>T->Y)
	{
		T->Right=Insert(Y,N,T->Right);
		if(Height(T->Right)-Height(T->Left)==2)
		  if(Y>T->Right->Y)
		    T=SingleRotateWithRight(T);
	      else
	        T=DoubleRotateWithRight(T);
		
	}
	
	T->Height=Max(Height(T->Left),Height(T->Right))+1;
	return T;
}

AvlTree 
FindNode(int X,AvlTree T)
{
	if(T==NULL)
	  return NULL;
	if(X<T->Element)
	  return FindNode(X,T->Left);
	else if(X>T->Element)
	  return FindNode(X,T->Right);
	else return T;
}

static AvlTree
SingleRotateWithLeft(AvlTree K2)
{
	AvlTree K1;
	
	K1=K2->Left;
	K2->Left=K1->Right;
	K1->Right=K2;
	
	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	
	K1->Height=Max(Height(K1->Left),Height(K2->Right))+1;
	
	return K1;
}

static AvlTree
SingleRotateWithRight(AvlTree K2)
{
	AvlTree K1;
	
	K1=K2->Right;
	K2->Right=K1->Left;
	K1->Left=K2;
	
	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	
	K1->Height=Max(Height(K1->Left),Height(K2->Right))+1;
	
	return K1;
}

static AvlTree
DoubleRotateWithLeft(AvlTree K3)
{
	K3->Left=SingleRotateWithRight(K3->Left);
	
	return SingleRotateWithLeft(K3);
}

static AvlTree
DoubleRotateWithRight(AvlTree K3)
{
	K3->Right=SingleRotateWithLeft(K3->Right);
	
	return SingleRotateWithRight(K3);
}

int Max(int X1,int X2)
{
	if(X1>X2)
	  return X1;
	else 
	  return X2;
}

void InsertCoordinate(int X, int Y, int N, Region R)
{   
    R->Yaxis[X]=Insert(Y, N, R->Yaxis[X]);
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
	R->Yaxis=malloc(sizeof(AvlTree)*(Capacity+1));
	if(R->Yaxis==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	for(i=1;i<Capacity+1;i++)
	 R->Yaxis[i]=NULL;
	 
	return R;
}

void
Traversal(Region R)
{
	Pretraversal(R->Yaxis[1]);
}

int flag,Count;

int
Pretraversal(AvlTree T)
{    
     if(T!=NULL)
     { if(T->StartOrEnd!=End||T->StartOrEnd!=Start)
       {
     	Count+=T->Element;
     	if(flag!=End)
     	flag=Pretraversal(T->Left);
     	else return;
     	flag=Pretraversal(T->Right);
       }
       else return flag=T->StartOrEnd;
     }
}

void Find(int Xmin, int Xmax, int Ymin, int Ymax, Region R)
{
	int i;
	AvlTree Tmp;
	long Count=0;
	for(i=Xmin;i<=Xmax;i++)
	{
		Tmp=FindNode(Ymin,R->Yaxis[i]);
		if(Tmp==NULL)
        R->Yaxis[i]=OrdinaryInsert(Ymin,R->Yaxis[i],Start);
        Tmp=FindNode(Ymax,R->Yaxis[i]);
		if(Tmp==NULL)
        R->Yaxis[i]=OrdinaryInsert(Ymax,R->Yaxis[i],End); 
        Count+=Pretraversal(R->Yaxis[i]);
        
	}
	printf("%d\n", Count);
}

AvlTree
OrdinaryInsert(int X, AvlTree T, int StartOrEnd)
{
	if(T==NULL) 
	{
	   T=malloc(sizeof(struct AvlNode));
	   T->Y=X;
	   T->Element=0;
	   T->Left=T->Right=NULL;
	   T->StartOrEnd=StartOrEnd;
    }
	else if(X<T->Y)
	   T->Left=OrdinaryInsert(X,T->Left,StartOrEnd);
	else if(X>T->Y)
	   T->Right=OrdinaryInsert(X,T->Right, StartOrEnd);
	
	return T;
}

void Tvs(AvlTree T)
{
    if(T!=NULL)
	{ 
	    printf("%d\n", T->Y);
		Tvs(T->Left);
		Tvs(T->Right);
	}
	return;
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
    		InsertCoordinate(X,Y,N,R);
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
