#include "stdio.h"
#include "stdlib.h"

int cmp(const void *a, const void *b)/* function for qsort */
{
       return *(int*)a-*(int*)b;
}

int find(int x,int *list,int n)
{
	int i;
	for(i=0;i<n;i++){
		if(list[i]==x)
		   return i;
	}
}


int main()
{
	char Filename[10],Filename2[10];
	int *input,*output;
	int inputnum,firstinsertposition,outputsize,start=-1;
	int i,j,k,tmp,count=0,flag=0;
	
	scanf("%s",&Filename);
	
	if (freopen(Filename, "r", stdin) == NULL)
	{
		printf("cannot open the file!");  
		exit(0);
	};
	
	scanf("%d",&inputnum);
	input=(int*)malloc(inputnum*sizeof(int));
	output=(int*)malloc(inputnum*sizeof(int));
	memset(output,0,inputnum*sizeof(int));
	for(i=0;i<inputnum;i++){
		scanf("%d",&input[i]);
		if(input[i]<0) start=i;	
		if(i+1<inputnum)
		   getchar();
	}
	
	
	j=0;
	for(i=0;i<inputnum;i++){/*先把没有经过后移的数找出来排序*/ 
		if(input[i]>=0&&input[i]%inputnum==i)
		   output[j++]=input[i];
	} 
	outputsize=j;
	qsort(output, outputsize, sizeof(int), cmp);

    if(start==-1){/*如果input中没有负数，人为设定start*/
    i=0;
    while(i<inputnum){
    	if(input[i]>=0&&input[i]%inputnum!=i&&input[input[i]%inputnum]%inputnum==input[i]%inputnum){
    	   start=i-1;
    	   if(start<0)
		    start=start+inputnum;
		    break;
		}
		i++;
    }
    }
	
	i=start+1;	
	while(i!=start&&i!=start+inputnum){/*再把经过后移的数插入排序*/ 
		if(i>=inputnum)
		    i=i-inputnum;
		if(input[i]>=0&&input[i]%inputnum!=i){
			firstinsertposition=input[i]%inputnum;
			j=find(input[firstinsertposition],output,outputsize);/*找到input【i】第一次插入处的数在output中的位置*/
			k=firstinsertposition;
			while(k!=i&&k!=i+inputnum){/*找到input【i】在output中的应插入的位置*/
		    	if(k>=inputnum)
		           k=k-inputnum;
				tmp=find(input[k],output,outputsize);
				if(tmp>j) j=tmp;
				k++;
			}
			if(flag==1){ flag=0;continue;}
			for(k=j+1;k<outputsize;k++){/*使这个数列最小*/
				if(output[k]>input[i]){
					j=k-1;break;
				} 
			}
			for(k=outputsize;k>j;k--){/*给插入数腾处空间*/
				output[k]=output[k-1];
			}
			outputsize++;
			output[j+1]=input[i];
		}
		   i++;
	} 
	
	if (freopen("4.out", "r", stdin) == NULL)
	{
		printf("cannot open the file!");  
		exit(0);
	};
	
	for(i=0;i<outputsize;i++){
		scanf("%d ",&input[i]);
		if(input[i]==output[i])
		printf("%d",output[i]);
		else
		printf("!\n");
		if(i!=outputsize-1)
		   printf(" ");
	}
	return 0;
} 
