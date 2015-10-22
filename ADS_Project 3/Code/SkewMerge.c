#include<stdio.h>
#include<stdlib.h>

typedef struct heap * heapnode;

//Define the node structure of Skew heap
struct heap{
	int num;
	heapnode lchild;
	heapnode rchild;
};

heapnode Merge(heapnode h1, heapnode h2);
heapnode Merge1(heapnode h1, heapnode h2);
heapnode BuildSkew(void);

//The driving routine for merging skew heaps
heapnode Merge(heapnode h1, heapnode h2){
	if(h1==NULL)
		return h2;
	if(h2==NULL)
		return h1;
	//To decide that which heap's root is smaller
	if(h1->num < h2->num)
		return Merge1(h1,h2);
	else
		return Merge1(h2,h1);
}

//The actual routine to merge skew heaps
heapnode Merge1(heapnode h1, heapnode h2){
	heapnode tmp;
	if(h1->lchild==NULL)
		h1->lchild = h2;
	else{
		//Using recursive way to do the same operation
		h1->rchild = Merge(h1->rchild, h2);
		//Do the swapping directly
		tmp = h1->lchild;
		h1->lchild = h1->rchild;
		h1->rchild = tmp;
	}
	return h1;
}

//The function to build a skew heap
heapnode BuildSkew(){
	int i,size;
	heapnode head,ptr;
	head = (heapnode)malloc(sizeof(struct heap));
	scanf("%d",&size);
	scanf("%d",&(head->num));
	head->lchild = NULL; head->rchild = NULL;
	for(i=2;i<=size;i++){
		ptr = (heapnode)malloc(sizeof(struct heap));
		scanf("%d",&(ptr->num));
		ptr->lchild = NULL; ptr->rchild = NULL;
		//Using the function Merge to build the heap,
		//regarding each new node as a skew heap with only one element
		head = Merge(head,ptr);
	}
	return head;
}

int main(){
	heapnode h1,h2;
	//Build the two heaps to merge
	h1=BuildSkew();
	h2=BuildSkew();
	//Merge the two heaps
	h1 = Merge(h1,h2);
}
