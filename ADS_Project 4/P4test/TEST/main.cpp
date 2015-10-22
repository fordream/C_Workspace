#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#define cmax 64
#define max 63000
#define MAX 63000
 //最大频率
#define Filename "Ex2random.in"
clock_t  start, stop; /* clock_t is a built-in type for processor time (ticks) */
double  duration;  /* records the run time (seconds) of a function */


struct code//code is used to store c[i], f[i] temporarily
{
	char c;//c[i]
	int f;//f[i]
};
struct node//the node of haffmantree
{
	struct node *lc;//leftchild
	struct node *rc;//rightchild
	int fre;// the frequency
	char value;// if the node stores a character, value = character, else value=0
	int codelen;//the lenth of the haffmancode(ex. 00001's codelen is 5)
};

struct node* new_node(void)//get a new memory
{
	struct node *newnode = (struct node*)malloc(sizeof(struct node));
	newnode->fre = MAX;
	newnode->lc = newnode->rc = NULL;
	newnode->value = 0;
	newnode->codelen = 0;
	return newnode;
}

void haff_free(struct node *n){        //free a haffman tree
	if(n == NULL) return;
	if(n->lc == NULL && n->rc == NULL){
		free(n);
		return;
	}
	haff_free(n->lc);
	haff_free(n->rc);

}
/*这是minheap的代码
我会补上的
struct node* deletemin(struct node * haff[], int m)
{
	int i=1;
	struct node *tmp;
	tmp = haff[1];
	while(haff[i]>haff[i]i<m){
	    i*=2;
		if(haff[i]->fre > haff[i+1]->fre)
		    i++

	}
}
struct node* haffman(struct code co[], int m)
{
	int i,j;
	struct node *firstmin, *secondmin;
	struct node *haff[cmax];
	for(i=1;i<=m;i++){   //this circulate is used to build a MinTree
		haff[i] = new_node();
		haff[i]->fre=co[i].f;
		haff[i]->value = co[i].c;
	}
	while(m > 1){
	   firstmin = deletemin(haff, m);
	   m--;
	   secondmin = deletemin(haff, m);
	   m--;
	   insert(firstmin, secondmin, haff, m);
	   m++;
	}
}*/
//这个是用队列实现的，时间复杂度是N的平方，暂时先用用……
struct node* haffman(struct code co[], int m)
{
	int i,j;
	struct node *swap, *newnode;
	struct node *haff[cmax];
	for(i=0;i<m;i++){
		haff[i] = new_node();
		haff[i]->fre=co[i].f;
		haff[i]->value = co[i].c;
	}
	haff[i] = new_node();
	for(i=0;i<m-1;i++){
		newnode = new_node();
		newnode->fre = haff[i]->fre+haff[i+1]->fre;
		newnode->lc = haff[i];
		newnode->rc = haff[i+1];
		haff[i+1] = newnode;
		for(j=i+1;j<m;j++){
		    if(haff[j]->fre>haff[j+1]->fre){
			    swap = haff[j];
				haff[j] = haff[j+1];
				haff[j+1] = swap;
			}
		}
	}
	return haff[m-1];
}

int cmp(const void* a,const void* b) // surpport the "qsort" function
{
	const code *aa = (const code*)a;
	const code *bb = (const code*)b;
	return(aa->f-bb->f);
}

void travel(struct node* haff, int hafflen, int h)    // travel a haffman tree and get the haffman code lenth
{
	h++;//h represents depth of a node
	if(haff->value != 0){
		haff->codelen = h-1;
		hafflen+=haff->fre*haff->codelen;
		return;
	}
	travel(haff->lc, hafflen, h);
	travel(haff->rc, hafflen, h);
}

int haff_test(struct code co[], int m)
	//test the haffman tree built by student, if it is a haffman tree, return his haffman code lenth, else return -1
{
	int i,j,hafflen=0;
	char c;
	struct node* tree, *temp;
	tree = new_node();
	for(i=0;i<m;i++){
		getchar();
	    getchar();
		j=0;
		temp = tree;
		c = getchar();
		while(c != '\n'){
			j++;
		    if(c == '0'){         //'0'represents left child
				if(temp->lc == NULL)
					temp->lc = new_node();
				else if(temp->lc->value != 0){
					return -1;
				}
				temp = temp->lc;
			}
			else if(c == '1'){          //'1'represents right child
				if(temp->rc == NULL)
					temp->rc = new_node();
				else if(temp->rc->value != 0){
					return -1;
				}
				temp = temp->rc;
			}
			c = getchar();
		}
		if(temp->lc!=NULL || temp->rc!=NULL) return -1;
		temp->fre = co[i].f;
		temp->value = co[i].c;
		temp->codelen = j;
		hafflen+=temp->fre*temp->codelen;
	}
	return hafflen;
	haff_free(tree);
}


void function()
{

	struct code co[cmax], cod[cmax];
	struct node *haff;
	int i,n,m;
	int hafflen, h=0, test;
	double j;

	start = clock();
	for(j=0;j<10000;j++)
	{
	if(freopen(Filename,"r",stdin)==NULL)
	 {
	 	exit(0);
	 }
	scanf("%d",&m);
	for(i=0;i<m;i++){
		getchar();
		co[i].c = getchar();
		getchar();
		scanf("%d", &co[i].f);
		cod[i].c = co[i].c;
		cod[i].f = co[i].f;
	}

    	    }
    stop = clock();
	duration = ((double)(stop - start))/CLK_TCK;
    printf("%f\n", duration);

	qsort(co, m, sizeof(code), cmp);
	haff = haffman(co, m);

	/*hafflen = 0;
	travel(haff, hafflen, h);
	scanf("%d", &n);
	getchar();
	    	haff_free(haff);for(i=0;i<n;i++){
		test = haff_test(cod, m);
		if(test == -1 || test != hafflen){
		    //printf("No\n");
		}
		else{
		    //printf("Yes\n");
		}
		}*/

    	haff_free(haff);
}

main ( )
{
    int i;
    void function();
    for(i=1;i<=5;i++)
    function();
    return 1;
}
