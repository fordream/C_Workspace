#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct HashRecord
{
	int Capacity;
	int *HashTable;
};

int main()
{
	FILE *fp;
    struct HashRecord Hashing;
	int i,TableSize,TotalNum,Num,Probe;
	char Filename[80];
	
	printf("Insert Filename:");
	scanf("%s", Filename);
	fp=fopen(Filename,"w");
	
	srand((unsigned)time(NULL)); 
	
	printf("Input Table Size:");
	scanf("%d", &TableSize);
	printf("Input TotalNum:");
	scanf("%d", &TotalNum);
	Hashing.HashTable=(int*)malloc(sizeof(int)*TableSize);
	memset(Hashing.HashTable,-1,TableSize*sizeof(int));
	for(i=0;i<TotalNum;i++)
	{
		Num=i;
		Probe=Hash(Num,TableSize);
		if(Hashing.HashTable[Probe]==-1);
		else
		{
			while(Hashing.HashTable[Probe]!=-1)
			 {
			 	Probe++;
			 	if(Probe>=TableSize)
			 	 Probe-=TableSize;
			 }		
		}
		Hashing.HashTable[Probe]=Num;
	}
	
	fprintf(fp,"%d\n",TableSize); 
	for(i=0;i<TableSize;i++)
	fprintf(fp,"%d ",Hashing.HashTable[i]);
    fclose(fp);
} 

int Hash(int Num, int TableSize)
{
	return Num%TableSize; 
}
