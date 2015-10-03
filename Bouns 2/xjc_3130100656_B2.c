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
};

int Login(int i,struct AccountInfo *Input,struct AccountInfo *T)
{  if(T==NULL)
      return 0;                   //ERROR: Account Not Exist
   if(Input[i].Account<T->Account)
      Login(i,Input,T->Left);
   else if(Input[i].Account>T->Account)
      Login(i,Input,T->Right);
   else 
   if(strcmp(T->Password,Input[i].Password)==0)return 1; //Log in successfully
   else return -1; //ERROR: Wrong Password
}

int RFind(int i,struct AccountInfo *Input,struct AccountInfo *T)
{  if(T==NULL)
      return 0;                   //Register Successful
   if(Input[i].Account<T->Account)
      RFind(i,Input,T->Left);
   else if(Input[i].Account>T->Account)
      RFind(i,Input,T->Right);
   else return 1;                 //ERROR: Account Number Already Exists 
}

struct AccountInfo *RInsert(int i,struct AccountInfo *Input, struct AccountInfo *T)
{  if(T==NULL){
      T=malloc(sizeof(struct AccountInfo));
      T->Account=Input[i].Account;
      strcpy(T->Password,Input[i].Password); 
      T->Left=T->Right=NULL;  }
   else
   if(Input[i].Account>T->Account)
      T->Right=RInsert(i,Input,T->Right);
   else if(Input[i].Account<T->Account)
      T->Left=RInsert(i,Input,T->Left);     //if the account has been already registered, we will not run this function
     
   return T;           
}

int main(void)
{  
   int i,N;
   int Login(int i,struct AccountInfo *Input,struct AccountInfo *T);
   int RFind(int i,struct AccountInfo *Input,struct AccountInfo *T);
   struct AccountInfo *RInsert(int i,struct AccountInfo *Input, struct AccountInfo *T);
   
   struct AccountInfo *T;
   T=NULL;
   
   if(freopen(Filename,"r",stdin)==NULL)
    exit(0);
	 
   scanf("%d",&N);
   struct AccountInfo *Input=(struct AccountInfo *)malloc(sizeof(struct AccountInfo)*N);
   for(i=0;i<N;i++)
      scanf("%c %l64d %s",&Input[i].choice,&Input[i].Account,Input[i].Password);    //Input
   
   for(i=0;i<N;i++)
   {  if(Input[i].choice=='L')
        if(Login(i,Input,T)==0)printf("ERROR: Account Not Exist\n");
        else if(Login(i,Input,T)==1)printf("Log in Successful\n");
        else if(Login(i,Input,T)==-1)printf("ERROR: Wrong Password\n");
      if(Input[i].choice=='R')
        if(RFind(i,Input,T)==1)printf("ERROR: Account Number Already Exists\n");
        else if(RFind(i,Input,T)==0)
             {RInsert(i,Input,T);
              printf("Register Successful\n");}
   } 
   system("pause");  
}
