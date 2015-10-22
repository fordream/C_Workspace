#include<stdio.h>
#include<stdlib.h>

struct LineTreeNode;
struct XaxisRecord;
typedef struct LineTreeNode *LineTree;
typedef struct XaxisRecord *Region;

void Insert(int Xmin, int Xmax, int Ymin, int Ymax, Region R);
Region Initialize(Region R, int Capacity); 
LineTree CreateLineTree(int LeftBoarder, int RightBoarder);
void Traverse(Region R);
void TraverseTree(LineTree L);

struct LineTreeNode
{
	int LeftBoarder;
	int RightBoarder;
	int SumOfChild;
	LineTree Left;
	LineTree Right;
	int Element;
};
struct XaxisRecord
{
	int Capacity;
	LineTree *Yaxis; 
};

LineTree
CreateLineTree(int LeftBoarder, int RightBoarder)
{  
    LineTree L;
	if(LeftBoarder==RightBoarder)
	{
	  	L=malloc(sizeof(struct LineTreeNode));
	  	L->LeftBoarder=LeftBoarder;
	  	L->RightBoarder=RightBoarder;
	    L->Element=0;
	  	L->Left=L->Right=NULL;
	  	return;
	}
	else
	{
		L=L=malloc(sizeof(struct LineTreeNode));
	  	L->LeftBoarder=LeftBoarder;
	  	L->RightBoarder=RightBoarder;
	  	L->Element=0;
	  	L->Left=CreateLineTree(LeftBoarder,(LeftBoarder+RightBoarder)/2);
	  	L->Right=CreateLineTree((LeftBoarder+RightBoarder)/2+1,RightBoarder);
	}
	
	return L;  
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
	R->Yaxis=malloc(sizeof(LineTree)*(Capacity+1));
	if(R->Yaxis==NULL)
	{ printf("Out of space");
	  exit(0);
	}
	for(i=1;i<Capacity+1;i++)
	 R->Yaxis[i]=CreateLineTree(1,Capacity);
	 
	return R;
}

void
Traverse(Region R)
{
	TraverseTree(R->Yaxis[1]);
}

void
TraverseTree(LineTree L)
{
	if(L!=NULL)
	{
		printf("%d %d\n", L->LeftBoarder, L->RightBoarder);
		TraverseTree(L->Left);
		TraverseTree(L->Right);
	}
	return;
}
int main(void)
{
	Region R;
	R=Initialize(R,10000);
    Traverse(R);
}

