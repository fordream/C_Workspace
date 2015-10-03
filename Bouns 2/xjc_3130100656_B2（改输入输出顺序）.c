/* Author: Feng Leying;  ID: 3130100656;  No.02 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Filename "0.in"

struct AccountInfo
{  unsigned long long Account;
   char Password[16];
   char choice;
   struct AccountInfo *Left;
   struct AccountInfo *Right;
   int  Height; 
};

struct AccountInfo *Find(int i,struct AccountInfo *Input,struct AccountInfo *T)
{  
   if(T==NULL)
      return NULL;                   //Account Not Exist
   if(Input[i].Account<T->Account)
      return Find(i,Input,T->Left);
      else if(Input[i].Account>T->Account)
           return Find(i,Input,T->Right);
      else if(Input[i].Account==T->Account)
           return T;
}

int Max(int a,int b)
{
	int t;
    t=a>b?a:b;
    return t;
}

int Height(struct AccountInfo * P)
{
	if(P==NULL)
	   return -1;
	else return P->Height;
}

struct AccountInfo *SingleRotateWithLeft(struct AccountInfo *K2)
{
	struct AccountInfo *K1;
	K1=K2->Left;
	K2->Left=K1->Right;
	K1->Right=K2;
	
	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	K1->Height=Max(Height(K1->Left),Height(K1->Right))+1;
	
	return K1;
}

struct AccountInfo *SingleRotateWithRight(struct AccountInfo *K2)
{
	struct AccountInfo *K1;
	K1=K2->Right;
	K2->Right=K1->Left;
	K1->Left=K2;
	
	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	K1->Height=Max(Height(K1->Left),Height(K1->Right))+1;
	
	return K1;
}

struct AccountInfo *DoubleRotateWithLeft(struct AccountInfo *K3)
{
	K3->Left=SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

struct AccountInfo *DoubleRotateWithRight(struct AccountInfo *K3)
{
	K3->Right=SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

struct AccountInfo *RInsert(int i,struct AccountInfo *Input, struct AccountInfo *T)
{  if(T==NULL){
      T=(struct AccountInfo *)malloc(sizeof(struct AccountInfo*));
      T->Account=Input[i].Account;
      strcpy(T->Password,Input[i].Password); 
      T->Left=T->Right=NULL;
	  T->Height=0;  }
   else
   if(Input[i].Account>T->Account){
      T->Right=RInsert(i,Input,T->Right);
      if(Height(T->Right)-Height(T->Left)==2)                   //ensure that the tree is balance
         if(Input[i].Account>T->Right->Account)
            T=SingleRotateWithRight(T);
         else T=DoubleRotateWithRight(T);
   }
   else if(Input[i].Account<T->Account){
      T->Left=RInsert(i,Input,T->Left);    
      if(Height(T->Left)-Height(T->Right)==2)
         if(Input[i].Account<T->Left->Account)
            T=SingleRotateWithLeft(T);
         else T=DoubleRotateWithLeft(T);
   } //if the account has been already registered, we will not run this function}
   T->Height=Max(Height(T->Left),Height(T->Right))+1;  
   return T;          
}

int main(void)
{  
   int i;
   int N;
   struct AccountInfo *T=NULL;//=(struct AccountInfo *)malloc(sizeof(struct AccountInfo *)*N);
   struct AccountInfo *Input=NULL;//=(struct AccountInfo *)malloc(sizeof(struct AccountInfo *));
   struct AccountInfo *P=NULL;//=(struct AccountInfo *)malloc(sizeof(struct AccountInfo *));
   Input=(struct AccountInfo *)malloc(sizeof(struct AccountInfo)*N);
   P=(struct AccountInfo *)malloc(sizeof(struct AccountInfo));   
  
   if(freopen(Filename,"r",stdin)==NULL)exit(0);

   scanf("%d",&N);

   
   for(i=0;i<N;i++){
      getchar();
   	  Input[i].choice=getchar();
      scanf("%l64d %s",&Input[i].Account,Input[i].Password);    //Input
   }
   
   for(i=0;i<N;i++){                               //print the result
      if(Input[i].choice==76){
      	P=Find(i,Input,T);
	    if(P==NULL)printf("ERROR: Not Exist\n");
        else if(strcmp(P->Password,Input[i].Password)==0)printf("Login: OK\n");
             else printf("ERROR: Wrong PW\n");
	  }
    
      else{
      	P=Find(i,Input,T);
        if(P==NULL) 
		  {T=RInsert(i,Input,T);
           printf("New: OK\n");}
		else printf("ERROR: Exist\n");
	  }
        
   } 

   system("pause");  
}
