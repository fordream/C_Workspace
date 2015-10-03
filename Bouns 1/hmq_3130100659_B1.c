/* Author: Lu Kuan;  ID: 3130100659;  No.01 */
#include<stdio.h>
#include<stdlib.h>
#define False 0
#define True 1
#define Normal 3
#define Vip 4
#define Filename "8.in"

struct Time{
	int Hour;
	int Minute;
	int Second;
};

struct TTQueue{
	struct Time ArriveTime,ServeTime;
	int Duration;
	int VipOrNot;
}; 

struct TableRecord
{
	struct Time CurrentTime;
	int Count;
	int VipOrNot;
};
    
    int MinTime(struct TableRecord *TableRecord, int TableNum);
    int TimeCmp(struct Time a, struct Time b);
    int FindVipWaiting(struct TTQueue *TTQueue, struct Time CurrentTime, int i);
    int ConvertToInt(struct Time Time1, struct Time Time2); 
    struct Time TableTimeRefresh(struct Time CurrentTime, int Duration);
    int AssignVipOrNot(int AssignTableIndex,int VipTableNum, int *VipTableIndex);
    int VipTableAvailable(int k,struct TTQueue *VipQueue, struct TableRecord *TableRecord, int *VipTableIndex, int VipTableNum); 
    
    int cmp(const void *a, const void *b)
    {
	if (((struct TTQueue *)a)->ArriveTime.Hour - ((struct TTQueue *)b)->ArriveTime.Hour)
		return ((struct TTQueue *)a)->ArriveTime.Hour - ((struct TTQueue *)b)->ArriveTime.Hour;
	else if(((struct TTQueue *)a)->ArriveTime.Minute - ((struct TTQueue *)b)->ArriveTime.Minute)	
		return ((struct TTQueue *)a)->ArriveTime.Minute - ((struct TTQueue *)b)->ArriveTime.Minute;
	else
		return ((struct TTQueue *)a)->ArriveTime.Second - ((struct TTQueue *)b)->ArriveTime.Second;
    }
   
    int cmp1(const void *a, const void *b)
    {
	if (((struct TTQueue *)a)->ServeTime.Hour - ((struct TTQueue *)b)->ServeTime.Hour)
		return ((struct TTQueue *)a)->ServeTime.Hour - ((struct TTQueue *)b)->ServeTime.Hour;
	else if(((struct TTQueue *)a)->ServeTime.Minute - ((struct TTQueue *)b)->ServeTime.Minute)	
		return ((struct TTQueue *)a)->ServeTime.Minute - ((struct TTQueue *)b)->ServeTime.Minute;
	else
		return ((struct TTQueue *)a)->ServeTime.Second - ((struct TTQueue *)b)->ServeTime.Second;
    }
    
int main(void)
{
    int nPeople,i,j,k;
    int NormalCount=0,VipCount=0,count;
    int TableNum,VipTableNum,AssignTableIndex,AssignQueue; 
    int *VipTableIndex;
    struct TableRecord *TableRecord;
    struct TTQueue *TTQueue,*VipQueue,*NormalQueue;
    struct Time Temp;

    scanf("%d", &nPeople);
    TTQueue=malloc(sizeof(struct TTQueue)*nPeople);
    VipQueue=malloc(sizeof(struct TTQueue)*nPeople);
    NormalQueue=malloc(sizeof(struct TTQueue)*nPeople);
    
    j=k=0;
    for(i=0;i<nPeople;i++)
    {
     	scanf("%d:%d:%d %d %d", &(TTQueue[i].ArriveTime.Hour),&(TTQueue[i].ArriveTime.Minute),&(TTQueue[i].ArriveTime.Second),&(TTQueue[i].Duration),&(TTQueue[i].VipOrNot));
     	if(TTQueue[i].VipOrNot==True)	
     	  {
     	  	VipQueue[k++]=TTQueue[i];
     	  	VipCount++;
     	  }
     	else
     	  {
     	  	NormalQueue[j++]=TTQueue[i];
     	  	NormalCount++;
     	  }
	}

	scanf("%d %d", &TableNum, &VipTableNum);
	TableRecord=malloc(sizeof(struct TableRecord)*TableNum);
	VipTableIndex=malloc(sizeof(int)*VipTableNum);
	
	for(i=0;i<VipTableNum;i++)
	{
		scanf("%d", &VipTableIndex[i]);
		VipTableIndex[i]--;
	}
	

 	for(i=0;i<TableNum;i++)
	{
		TableRecord[i].Count=TableRecord[i].CurrentTime.Minute=TableRecord[i].CurrentTime.Second=0;
		TableRecord[i].CurrentTime.Hour=8;
		TableRecord[i].VipOrNot=False;
	}
	
	for(i=0;i<VipTableNum;i++)
	TableRecord[VipTableIndex[i]].VipOrNot=True;
	
	qsort(VipQueue,VipCount, sizeof(struct TTQueue), cmp);
	qsort(NormalQueue,NormalCount,sizeof(struct TTQueue),cmp);
	
for(i=j=k=0;i<nPeople;i++) 
{    
     if(k==VipCount) VipQueue[k].ArriveTime.Hour=10000;
     if(j==NormalCount) NormalQueue[j].ArriveTime.Hour=10000;
     
     if(TimeCmp(NormalQueue[j].ArriveTime,VipQueue[k].ArriveTime))
       AssignQueue=Vip;
     else AssignQueue=Normal;
     
     AssignTableIndex=MinTime(TableRecord,TableNum);

     
     if(AssignQueue==Normal&&AssignVipOrNot(AssignTableIndex,VipTableNum,VipTableIndex))
     {
     	if(TimeCmp(TableRecord[AssignTableIndex].CurrentTime,VipQueue[k].ArriveTime))
     	AssignQueue=Vip;
     }
     
     if(AssignQueue==Normal)
     {
     	for(count=0;count<TableNum;count++)
     	 if(TimeCmp(NormalQueue[j].ArriveTime,TableRecord[count].CurrentTime))
     	  {
     	  	AssignTableIndex=count;
     	  	break;
     	  }
     }
     else if(AssignQueue==Vip)
     {
     	 for(count=0;count<TableNum;count++)
     	 if(TimeCmp(VipQueue[k].ArriveTime,TableRecord[count].CurrentTime))
     	  {
     	  	AssignTableIndex=count;
     	  	break;
     	  }
     }
     
     if(AssignQueue==Vip)
     {
     	for(count=0;count<VipTableNum;count++)
     	{
     		if(TableRecord[AssignTableIndex].CurrentTime.Hour==TableRecord[VipTableIndex[count]].CurrentTime.Hour&&TableRecord[AssignTableIndex].CurrentTime.Minute==TableRecord[VipTableIndex[count]].CurrentTime.Minute&&TableRecord[AssignTableIndex].CurrentTime.Second==TableRecord[VipTableIndex[count]].CurrentTime.Second)
     	    {
     	    	AssignTableIndex=VipTableIndex[count];
     	    	break;
     	    }
		}
     }
     
    if(AssignQueue==Vip&&VipTableAvailable(k,VipQueue,TableRecord,VipTableIndex,VipTableNum)) 
       AssignTableIndex=VipTableAvailable(k,VipQueue,TableRecord,VipTableIndex,VipTableNum)-1;
    
    
     if(TableRecord[AssignTableIndex].CurrentTime.Hour>=21)
      continue;
      
     if(AssignQueue==Vip) 
     {
      if(VipQueue[k].ArriveTime.Hour<8) 
      {
      	k++; continue;
      }
      if(VipQueue[k].ArriveTime.Hour>=21) continue;
	  if(TimeCmp(VipQueue[k].ArriveTime,TableRecord[AssignTableIndex].CurrentTime))
      TableRecord[AssignTableIndex].CurrentTime=VipQueue[k].ArriveTime;
		 
	  VipQueue[k].ServeTime=TableRecord[AssignTableIndex].CurrentTime;
	  if(VipQueue[k].ServeTime.Minute>=60)
	  {
	  	VipQueue[k].ServeTime.Minute-=60;
	  	VipQueue[k].ServeTime.Hour++;
	  }
      TableRecord[AssignTableIndex].CurrentTime=TableTimeRefresh(TableRecord[AssignTableIndex].CurrentTime, VipQueue[k].Duration);
      TableRecord[AssignTableIndex].Count++; 
      k++;
     }
     else
     {
      if(NormalQueue[j].ArriveTime.Hour<8)
      {
      	j++;continue;
      }
      if(NormalQueue[j].ArriveTime.Hour>=21) continue;
      if(TimeCmp(NormalQueue[j].ArriveTime,TableRecord[AssignTableIndex].CurrentTime))
      TableRecord[AssignTableIndex].CurrentTime=NormalQueue[j].ArriveTime;
		 
	  NormalQueue[j].ServeTime=TableRecord[AssignTableIndex].CurrentTime;
      TableRecord[AssignTableIndex].CurrentTime=TableTimeRefresh(TableRecord[AssignTableIndex].CurrentTime, NormalQueue[j].Duration);
      TableRecord[AssignTableIndex].Count++; 
      j++;
     }
}
    
    for(count=i=0;i<VipCount;i++)
      if(VipQueue[i].ServeTime.Hour>=8&&VipQueue[i].ServeTime.Hour<21)
      {
      TTQueue[i]=VipQueue[i];
      count++;
      }
    k=0;
    for(k=0;k<NormalCount;k++)
    {
    	if(NormalQueue[k].ServeTime.Hour>=8&&NormalQueue[k].ServeTime.Hour<21)
    		TTQueue[count++]=NormalQueue[k];
    }
      
    
    qsort(TTQueue,count, sizeof(struct TTQueue), cmp1);
    
    for(i=0;i<count;i++)
	 {
     printf("%02d:%02d:%02d ", TTQueue[i].ArriveTime.Hour,TTQueue[i].ArriveTime.Minute,TTQueue[i].ArriveTime.Second);
     printf("%02d:%02d:%02d %d\n",TTQueue[i].ServeTime.Hour,TTQueue[i].ServeTime.Minute,TTQueue[i].ServeTime.Second,ConvertToInt(TTQueue[i].ServeTime,TTQueue[i].ArriveTime));
	 }

    for(i=0;i<TableNum-1;i++)
	  printf("%d ", TableRecord[i].Count);
	printf("%d", TableRecord[TableNum-1].Count);
}

VipTableAvailable(int k,struct TTQueue *VipQueue, struct TableRecord *TableRecord, int *VipTableIndex, int VipTableNum)
{
	int i;
	struct Time Temp;
	for(i=0;i<VipTableNum;i++)
	{
		Temp=VipQueue[k].ArriveTime;
		Temp=TableRecord[VipTableIndex[i]].CurrentTime;
		if(TimeCmp(VipQueue[k].ArriveTime,TableRecord[VipTableIndex[i]].CurrentTime))
		return VipTableIndex[i]+1;
	}
	return 0; 
}

int TimeCmp(struct Time a, struct Time b)
{
	if(a.Hour>b.Hour) return 1;
	else if(a.Hour==b.Hour) 
	  if(a.Minute>b.Minute) return 1;
	  else if(a.Minute==b.Minute)
	      if(a.Second>b.Second) return 1;
    return 0;
}

int MinTime(struct TableRecord *TableRecord, int TableNum)
{
	struct Time Temp;
	int i,index;
	
	index=0;
	Temp=TableRecord[0].CurrentTime;
	for(i=1;i<TableNum;i++)
	{
    	if(TimeCmp(Temp,TableRecord[i].CurrentTime))
		  {Temp=TableRecord[i].CurrentTime;
		   index=i;}
	}
	return index;
}

int ConvertToInt(struct Time Time1, struct Time Time2)
{   
	struct Time Temp;
	int TempSecond,TempMinute,TempHour;
	TempSecond=Time1.Second-Time2.Second;
	TempMinute=Time1.Minute-Time2.Minute;
	TempHour=Time1.Hour-Time2.Hour;
	if(TempSecond<0) 
	 {
	  TempSecond=TempSecond+60;
	  TempMinute--;
     }
     if(TempMinute<0) 
	 {
	  TempMinute=TempMinute+60;
	  TempHour--;
     }
     if(TempSecond>=30)
	    TempMinute++;
	    
     return TempMinute+TempHour*60;
}

struct Time TableTimeRefresh(struct Time CurrentTime, int Duration)
{   
     if(Duration>=120)
      Duration=120;
	CurrentTime.Minute=CurrentTime.Minute+Duration;
	if(CurrentTime.Minute>=60)
	 {
	  CurrentTime.Minute-=60;
	  CurrentTime.Hour++; 
     }
    return CurrentTime;
}

int AssignVipOrNot(int AssignTableIndex, int VipTableNum, int *VipTableIndex)
{
	int i;
	for(i=0;i<VipTableNum;i++)
	  if(VipTableIndex[i]==AssignTableIndex) return True;
	return False;
}

