#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct info /* structure storing every person's information */
{
	char name[10];
	int age;
	long int net;
}info[100000];

int cmp(const void *a, const void *b)/* function for qsort */
{
	if (((struct info *)a)->net - ((struct info *)b)->net)		/* whether their net worths are different */
		return ((struct info *)b)->net - ((struct info *)a)->net;
	else if(((struct info *)a)->age - ((struct info *)b)->age)	/* whether their ages are different */
		return ((struct info *)a)->age - ((struct info *)b)->age;
	else
		return strcmp(((struct info *)a)->name, ((struct info *)b)->name);
}

int main(void)
{
	int i, j, k, maxNum, Amax, Amin, count;
	long int nPeople, nQueries, ageCount[205], pos[100000];
	memset(ageCount, 0, sizeof(ageCount));
	memset(pos, 0, sizeof(pos));
	/* array 'ageCount' records number of appearance of every distinct age */
	/* array 'pos' records the position of person whose age only appears no more than 100 times in previous positions */

	/* read in information */
	scanf("%ld %ld", &nPeople, &nQueries);
	for (i = 0; i < nPeople; i++)
		scanf("%s %d %ld", info[i].name, &(info[i].age), &(info[i].net));

	/* sort all information in order required in output */
	qsort(info, nPeople, sizeof(struct info), cmp);

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