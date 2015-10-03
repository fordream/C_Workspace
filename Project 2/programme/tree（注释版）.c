#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct info /* structure storing every person's information */
{
	char name[10];
	int age;
	long int net;
}info[100000], temp[100000];
/* array 'info' stores input information */
/* array 'temp' stores sorted information */

struct tree
{
	long int key; /* 'key' records the index of person's information in array 'info' */
	struct tree *l;
	struct tree *r;
} *T = NULL, *s[100000]; /* 'T' is header of tree */
/* array 's' serves as a stack while traversing the tree */

long int top = 0, l = 0;
/* 'top' records top location of the stack 's' */
/* 'l' is a variable used when we transfer information in line 88*/

int cmp(const void *a, const void *b)/* function for sorting */
{
	if (((struct info *)a)->net - ((struct info *)b)->net)		/* whether their net worths are different */
		return ((struct info *)b)->net - ((struct info *)a)->net;
	else if(((struct info *)a)->age - ((struct info *)b)->age)	/* whether their ages are different */
		return ((struct info *)a)->age - ((struct info *)b)->age;
	else
		return strcmp(((struct info *)a)->name, ((struct info *)b)->name);
}

void insert(int i) /* insert a node in the tree */
{
	struct tree *pos = T;
	if (T == NULL) /* tree is empty */
	{
		T = malloc(sizeof(struct tree));
		T->key = i;
		T->l = T->r = NULL;
		return;
	}
	while (1)
	{
		if (cmp(info+pos->key, info+i) > 0) /* key to insert is less than current node's */
		{
			if (pos->l == NULL) /* appropriate location found */
			{
				pos->l = malloc(sizeof(struct tree));
				pos->l->key = i;
				pos->l->l = pos->l->r = NULL;
				break;
			}
			else
				pos = pos->l; /* continue searching for appropriate location */
		}
		else /* key to insert is bigger than or equal to current node's */
		{
			if (pos->r == NULL) /* appropriate location found */
			{
				pos->r = malloc(sizeof(struct tree));
				pos->r->key = i;
				pos->r->l = pos->r->r = NULL;
				break;
			}
			else
				pos = pos->r; /* continue searching for appropriate location */
		}
	}
}

void traverse(void) /* in-order traverse a tree using iteration in case of segement fault caused by too many recursions */
{
	struct tree *pos = T;
	do
	{
		while (pos != NULL)
		{
			s[top++] = pos;
			pos = pos->l; /* push all nodes on the left into the stack */
		}
		if (top == 0) /* end when stack is empty */
			break;
		pos = s[--top]; /* pop from stack */
		temp[l++] = info[pos->key]; /* transfer information in sorted order */
		pos = pos->r; /* go right by one step */
	}
	while (1);
}

int main(void)
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	int i, j, k, maxNum, Amax, Amin, count;
	long int nPeople, nQueries, ageCount[205], pos[100000];
	memset(ageCount, 0, sizeof(ageCount));
	memset(pos, 0, sizeof(pos));

	/* array 'ageCount' records number of appearance of every distinct age */
	/* array 'pos' records the position of person whose age only appears no more than 100 times in previous positions */

	/* read in information */
	scanf("%ld %ld", &nPeople, &nQueries);
	for (i = 0; i < nPeople; i++)
	{
		scanf("%s %d %ld", info[i].name, &(info[i].age), &(info[i].net));
		insert(i);
	}
	
	traverse();/* transfer information from array 'info' to array 'temp' in order */
	for (i = 0; i < nPeople; i++)
	{
		info[i] = temp[i];
	}

	/* for maximun output number is 100, so it indicates redundency that a specific age appears more than 100 times */
	for (k = i = 0; i < nPeople; i++)
		if (++ageCount[info[i].age] < 101)
			pos[k++] = i;

	for (i = 0; i < nQueries; i++)
	{
		count = 0; /* reset the counter for output information */
		printf("Case #%ld:\n", i+1);
		scanf("%d %d %d", &maxNum, &Amin, &Amax);
		for (j = 0; j < k; j++) /* 'k' records the number of useful information */
		{
			if (info[pos[j]].age >= Amin && info[pos[j]].age <= Amax)/* check age location */
			{
				printf("%s %d %ld\n", info[pos[j]].name, info[pos[j]].age, info[pos[j]].net);
				if (++count == maxNum) /* increment 'count' and check whether it's adequate */
					break;
			}	
		}
		if (!count) /* when 'count' is zero, that is, no information has been printed */
			printf("None\n");
	}
	return 0;
}
