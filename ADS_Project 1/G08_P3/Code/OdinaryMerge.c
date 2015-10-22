#include<stdio.h>
#include<stdlib.h>
#define MAX 10000

typedef struct HeapStruct * PriorityQueue;

//Define the node structure of ordinary heap
struct HeapStruct{
	int Size;
	int *Elements;
};

//Set two array to store the elements of heap
int Heap1[20001];
int Heap2[20001];

PriorityQueue O_Insert(int num, PriorityQueue H);
PriorityQueue OrdinaryMerge(PriorityQueue h1, PriorityQueue h2);

//To read the data from input and build an ordinary heap
void Build_Heap(int *h, int *size){
    int i, tmp, child;
    
    //Store the data to the heap array
	scanf("%d", size);
	for(i=1;i<=*size;i++)
		scanf("%d",&h[i]);
		
	//Adjust the array to make it a heap
	for(i=*size/2;i>=1;i--)
	{
		child = i*2;
		while(child<=*size){
			//When the child come to the end of the heap, adjust the sequence
			if(child==*size)
			{
				if(h[child/2] > h[child]){
					tmp = h[child/2]; h[child/2] = h[child]; h[child] = tmp;
				}
				break; 
			}
			//Percolate down
			else
			{
				if(h[child] > h[child+1])
					child++;
				if(h[child]< h[child/2]){
				    tmp = h[child/2]; h[child/2] = h[child]; h[child] = tmp; child *= 2;
				}
				else break;
			}
		}
	}
}

//To insert one element to a heap
PriorityQueue O_Insert(int num, PriorityQueue H){
	int i;
	//To check whether the priority queue is full
	if(H->Size >= MAX){
		printf("Priority queue is full\n");
		return H;
	}
	//Percolate up
	for(i=++H->Size;H->Elements[i/2]>num;i/=2)
		H->Elements[i] = H->Elements[i/2];
	(H->Elements)[i] = num;
	return H;
}

//To merge two ordinary heaps
PriorityQueue OrdinaryMerge(PriorityQueue h1, PriorityQueue h2){
	int i;
	if(h1==NULL)
		return h2;
	if(h2==NULL)
		return h1;
	//Compare the size of two heap to decide that choose which one to be inserted
	if(h1->Size > h2->Size){
		//Insert the element from h2 to h1 one by one
		for(i=1;i<=h2->Size;i++)
			h1 = O_Insert(h2->Elements[i],h1);
		return h1;
	}
	else{
		//Insert the element from h2 to h1 one by one
		for(i=1;i<=h1->Size;i++)
			h2 = O_Insert(h1->Elements[i],h2);
		return h2;
	}
}

int main(){
	int i;
	PriorityQueue H1,H2,tmp;
	int *ptr;
	//Apply for the memory to store the information of heap
	H1 = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	H2 = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	//Build the two heaps to merge
	Build_Heap(Heap1,&(H1->Size));
	Build_Heap(Heap2,&(H2->Size));
	//To set the target array of the two heap and initial its minimum root
	H1->Elements = Heap1;	Heap1[0]=-1;
	H2->Elements = Heap2;	Heap2[0]=-1;
	//Merge the two heaps
	tmp = OrdinaryMerge(H1,H2);
}

