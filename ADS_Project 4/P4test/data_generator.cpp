#include<stdio.h>
#include<stdlib.h>
#define cmax 64
#define max 1000
#define MAX 1000 //×î´óÆµÂÊ
#define Filename "passage.in"

long ASCII[128];

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
	int codevalue;
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

void travel(struct node* haff, int &hafflen, int h)    // travel a haffman tree and get the haffman code lenth
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

int cmp(const void* a,const void* b) // sur对不起，翻译出错，请稍后再试。pport the "qsort" function
{
	const code *aa = (const code*)a;
	const code *bb = (const code*)b;
	return(aa->f-bb->f);
}

int BinarytoDecimal(int D)
{
     D=D%256;
	int Tmp=0;
	while(D!=0)
	{
		if(D%2==1)
		 Tmp=Tmp*10+1;
		else
		 Tmp=Tmp*10;
        D/=2;
	}
	return Tmp;
}

int main(void)
{
    FILE *fp;
    int i,j,m,count=0;
    int stu;
    char tmp;
    char fileout[20];
    struct code co[cmax], cod[cmax];
	struct node *haff;
	int hafflen, h=0, test;


	if((fp=fopen(Filename,"r"))==NULL)
	  exit(0);
	while(!feof(fp))
	{
		tmp=fgetc(fp);
		if(tmp>='A'&&tmp<='Z'||tmp>='a'&&tmp<='z'||tmp>='0'&&tmp<='9'||tmp==' ')
		ASCII[(int)tmp]++;
		if(ASCII[(int)tmp]>=1000)
		 ASCII[(int)tmp]=1000;
	}
	scanf("%s", fileout);
	if((fp=fopen(fileout,"w"))==NULL)
	  exit(0);
	  for(i=0;i<=127;i++)
	{
		if(ASCII[i]!=0)
		count++;
	}

	for(i=0,j=0;i<=127;i++)
	{
		if(ASCII[i]!=0)
		{
			co[j].c=(char)i;
			co[j].f=ASCII[i];
			j++;
		}
	}
		fprintf(fp,"%d\n",count-3);
		for(i=0;i<=127;i++)
	{
		if(ASCII[i]!=0&&i!=32&&i!='0'&&i!='1')
		fprintf(fp,"%c %d ",(char)i,ASCII[i]);
	}
	scanf("%d", &stu);
	fprintf(fp,"\n",stu);
	fprintf(fp,"%d\n",stu);
    for(j=1;j<=stu;j++)
	  for(i=0;i<=127;i++)
    	{
		if(ASCII[i]!=0&&i!=32&&i!='0'&&i!='1')
		fprintf(fp,"%c %d\n",(char)i,BinarytoDecimal(ASCII[i]+stu));
	    }
	fclose(fp);
	system("pause");
}
