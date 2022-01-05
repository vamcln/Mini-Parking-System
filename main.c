#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"parkinglot.h"

void displayvisitors(guestvehicle* ip)
{
    guestvehicle* temp;
    temp=ip;
    while(temp!=NULL)
    {
        printf("%d/%d/%d\n",ip->day,ip->mon,ip->year);
        printf("%s",ip->day_time);
        printf("vehicle number: %s  vehicle name:%s\n",(temp->vh).number,(temp->vh).name);
        if(temp->vh._2wheeler==true)
        {
         printf("vehicle type: 2 wheeler\n");
        }
        else
        {
         printf("vehicle type: 4 wheeler\n");
        }

        if((temp->psk.compact==true)&&(temp->vh._2wheeler==false))
        {
            printf("wing :%c allocated compact spots indices: %d and %d\n",temp->psk.wingid,temp->psk.index,temp->psk.index+1);
        }
        else
        {
            if(temp->psk.compact==true)
            {
                printf("wing : %c allocated compact spot index: %d\n",temp->psk.wingid,temp->psk.index);
            }
            else if(temp->psk.compact==false)
            {
                printf("wing : %c allocated large spot index: %d\n",temp->psk.wingid,temp->psk.index);
            }
        }
        temp=temp->next;
    }
}
int main()
{
   flat* apa[floorsinwing];
   flat* apb[floorsinwing];
   flat* apc[floorsinwing];
   level* lotto;int i,j,k;
   char ch='c';
   level* ptr;
   FILE* fp;
   fp=fopen("abc.txt","r");
   if(fp==NULL)
   {
       printf("UNABLE TO OPEN THE FILE\n");
       exit(1);
   }
   else
   {

    for(i=0;i<=2;i++)
    {
       lotto=(level*)malloc(sizeof(level));
       fscanf(fp,"%d %d",&lotto->noofcompactspots,&lotto->nooflargespots);

       for(j=0;j<sz;j++)
       {
           lotto->statuscompactspots[j]=0;
           lotto->mapcompact[j]=0;
           lotto->maplarge[j]=0;
           lotto->statuslargespots[j]=0;
       }

       lotto->wing=ch;
       k=(int)ch-1;
       ch=(char)k;
       lotto->next=ptr;
       ptr=lotto;
    }
    lotto=ptr;
    ((lotto->next)->next)->next=lotto;
    //printf("creation ok");
    allocate_flats(apa,'a',fp);
    allocate_flats(apb,'b',fp);
    allocate_flats(apc,'c',fp);
    //printf("create ok\n");
    permanentparkingspot(apa,lotto);
    permanentparkingspot(apb,lotto->next);
    permanentparkingspot(apc,(lotto->next)->next);
   // printf("send ok\n");
   // printf("%d    wertyui\n",county);
//    qsort(prr,county,sizeof(paire),comparator);
    msort_vdr(prr,0,pairscount-1);
    for(int o=0;o<pairscount;o++)
    {
        printf("%s %c %d\n",prr[o].v.number,prr[o].ps.wingid,prr[o].ps.index);
    }
   // printf("qsort ok\n");
    char sam[20];
    int y;
    guestvehicle* vpmain;
    vpmain=NULL;
int asd=0;
    while(asd==0)
    {
        printf("to park a vehicle press 1 else press 2\n");
        scanf("%d",&y);
        if(y==2)
        {
            asd=1;
        }
        else
        {
            printf("enter number of vehicle\n");
            scanf("%s",sam);
           vpmain=parkvehicle(sam,lotto,vpmain);
          // printf("parkveh ok\n");
        }

    }
    displayvisitors(vpmain);






}
return 0;
}
