#include<stdio.h>
#include<stdlib.h>
#define False 0
#define True 1
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

    int MinTime(struct TableRecord *TableRecord, int TableNum,int FindVipOrNot, int VipTableNum);
    int TimeCmp(struct Time a, struct Time b);
    int FindVipWaiting(struct TTQueue *TTQueue, struct Time CurrentTime, int i);
    int ConvertToInt(struct Time Time1, struct Time Time2); 
    struct Time TableTimeRefresh(struct Time CurrentTime, int Duration);
    
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
    int nPeople,i,k;
    int TableNum,VipTableNum,VipTableIndex,AssignTableIndex; 
    struct TableRecord *TableRecord;
    struct TTQueue *TTQueue;
    struct Time Temp;
    int digit1,digit2,digit3,digit4,digit5,digit6; 
    
    if(freopen(Filename, "r",stdin)==NULL)
     exit(0);
     
    scanf("%d", &nPeople);
    TTQueue=malloc(sizeof(struct TTQueue)*nPeople);
    for(i=0;i<nPeople;i++)
    {
     	scanf("%d:%d:%d %d %d", &(TTQueue[i].ArriveTime.Hour),&(TTQueue[i].ArriveTime.Minute),&(TTQueue[i].ArriveTime.Second),&(TTQueue[i].Duration),&(TTQueue[i].VipOrNot));
	}
	scanf("%d %d\n%d", &TableNum, &VipTableNum, &VipTableIndex);
	VipTableIndex--;
	TableRecord=malloc(sizeof(struct TableRecord)*TableNum);
 	for(i=0;i<TableNum;i++)
	{
		TableRecord[i].Count=0;
		TableRecord[i].CurrentTime.Hour=8;
		TableRecord[i].CurrentTime.Minute=0;
		TableRecord[i].CurrentTime.Second=0;
		TableRecord[i].VipOrNot=False;
	}
	
	TableRecord[VipTableIndex].VipOrNot=True;
	qsort(TTQueue, nPeople, sizeof(struct TTQueue), cmp);
	
    for(i=0;i<nPeople;i++) 
    {
    	
     if(TTQueue[i].ArriveTime.Hour>=21) break;
     
     AssignTableIndex=-1;
     
     for(k=0;k<TableNum;k++)
      {
      	if(TimeCmp(TTQueue[i].ArriveTime,TableRecord[k].CurrentTime)||TTQueue[i].ArriveTime.Hour==TableRecord[k].CurrentTime.Hour&&TTQueue[i].ArriveTime.Minute==TableRecord[k].CurrentTime.Minute&&TTQueue[i].ArriveTime.Second==TableRecord[k].CurrentTime.Second)
      	  { AssignTableIndex=k;break;}
      }
      
      if(AssignTableIndex==-1)
      AssignTableIndex=MinTime(TableRecord,TableNum,True,VipTableIndex); 
      
      if(TTQueue[i].VipOrNot==True&&TimeCmp(TTQueue[i].ArriveTime,TableRecord[VipTableIndex].CurrentTime))
        AssignTableIndex=VipTableIndex;
                    
      if(TTQueue[i].VipOrNot==False&&AssignTableIndex==VipTableIndex)
       { 
         if(FindVipWaiting(TTQueue,TableRecord[VipTableIndex].CurrentTime,i))
       	  AssignTableIndex=MinTime(TableRecord,TableNum,False,VipTableIndex);
       }
    
	  if(TableRecord[AssignTableIndex].CurrentTime.Hour>=21)
      continue;
      
	  if(TimeCmp(TTQueue[i].ArriveTime,TableRecord[AssignTableIndex].CurrentTime)||TTQueue[i].ArriveTime.Hour==TableRecord[AssignTableIndex].CurrentTime.Hour&&TTQueue[i].ArriveTime.Minute==TableRecord[AssignTableIndex].CurrentTime.Minute&&TTQueue[i].ArriveTime.Second==TableRecord[AssignTableIndex].CurrentTime.Second)
      TableRecord[AssignTableIndex].CurrentTime=TTQueue[i].ArriveTime;
		 
	 TTQueue[i].ServeTime=TableRecord[AssignTableIndex].CurrentTime;
     TableRecord[AssignTableIndex].CurrentTime=TableTimeRefresh(TableRecord[AssignTableIndex].CurrentTime, TTQueue[i].Duration);
     TableRecord[AssignTableIndex].Count++; 
    }
    
    qsort(TTQueue, nPeople, sizeof(struct TTQueue), cmp1);

    for(i=0;i<nPeople;i++)
    {  if(TTQueue[i].ServeTime.Hour!=0&&TTQueue[i].ServeTime.Hour<21)
         {
		 digit1=TTQueue[i].ArriveTime.Hour/10;
         digit2=TTQueue[i].ArriveTime.Hour%10;
		 digit3=TTQueue[i].ArriveTime.Minute/10;
		 digit4=TTQueue[i].ArriveTime.Minute%10;
		 digit5=TTQueue[i].ArriveTime.Second/10;
		 digit6=TTQueue[i].ArriveTime.Second%10; 
		 printf("%d%d:%d%d:%d%d ",digit1,digit2,digit3,digit4,digit5,digit6);
		 digit1=TTQueue[i].ServeTime.Hour/10;
         digit2=TTQueue[i].ServeTime.Hour%10;
		 digit3=TTQueue[i].ServeTime.Minute/10;
		 digit4=TTQueue[i].ServeTime.Minute%10;
		 digit5=TTQueue[i].ServeTime.Second/10;
		 digit6=TTQueue[i].ServeTime.Second%10; 
      	 printf("%d%d:%d%d:%d%d %d\n",digit1,digit2,digit3,digit4,digit5,digit6, ConvertToInt(TTQueue[i].ServeTime,TTQueue[i].ArriveTime));}
    }
    for(i=0;i<TableNum-1;i++)
	  printf("%d ", TableRecord[i].Count);
	printf("%d", TableRecord[TableNum-1].Count);
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

int MinTime(struct TableRecord *TableRecord, int TableNum,int FindVipOrNot, int VipTableIndex)
{
	struct Time Temp;
	int i,index,index1=0,index2=0;
	
	index=0;
	Temp=TableRecord[0].CurrentTime;
	for(i=1;i<TableNum;i++)
	{
    	if(TimeCmp(Temp,TableRecord[i].CurrentTime))
		  {Temp=TableRecord[i].CurrentTime;
		   index=i;}
	}
	if(FindVipOrNot==True)
	   return index;
	else if(VipTableIndex!=index)
	   return index;
	else 
	{   
	    index1=0;
	    Temp=TableRecord[0].CurrentTime;
		for(i=0;i<index;i++)
		{
    	if(TimeCmp(Temp,TableRecord[i].CurrentTime))
		  {Temp=TableRecord[i].CurrentTime;
		  index1=i;}
        }
        index2=index+1;
        Temp=TableRecord[index+1].CurrentTime;
        for(i=index+1;i<TableNum;i++)
        {
    	if(TimeCmp(Temp,TableRecord[i].CurrentTime))
		  {Temp=TableRecord[i].CurrentTime;
		  index2=i;}
        }
        if(TimeCmp(TableRecord[index1].CurrentTime,TableRecord[index2].CurrentTime)||index1==VipTableIndex)
           return index2;
        else return index1;
	}
}

int FindVipWaiting(struct TTQueue *TTQueue, struct Time CurrentTime, int i)
{
    while(TimeCmp(CurrentTime, TTQueue[i].ArriveTime)||CurrentTime.Hour==TTQueue[i].ArriveTime.Hour&&CurrentTime.Minute==TTQueue[i].ArriveTime.Minute&&CurrentTime.Second==TTQueue[i].ArriveTime.Second)
 	{
 	 	if(TTQueue[i].VipOrNot==True) return True;
 	 	i++;
 	}
 	 return False;	
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
	  Temp.Hour--;
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

