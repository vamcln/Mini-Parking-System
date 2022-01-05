#include"parkinglot.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void allocate_flats(flat* arr[],char ch,FILE* fp)
{
   flat *ip,*ip1;
   int i,j,k;
   arr[0]=NULL;
   for(j=1;j<floorsinwing;j++)
   {
       ip1=NULL;
       ip=NULL;
       for(i=flatsperfloor;i>=1;i--)
       {
           ip=(flat *)malloc(sizeof(flat));
           ip->next=ip1;
           ip->wing=ch;
           ip->flatid=(j*10)+i;
           fscanf(fp,"%d",&(ip->noof2wheelers));
          // printf("%d",ip->noof2wheelers);
           for(k=0;k<ip->noof2wheelers;k++)
           {
               fscanf(fp,"%s %s",(ip->v[k]).name,(ip->v[k]).number);
            //   printf("%s %s ",(ip->v[k]).name,(ip->v[k]).number);
               (ip->v[k])._2wheeler=true;
           }
           fscanf(fp,"%d",&(ip->noof4wheelers));
           for( ;k<((ip->noof2wheelers)+(ip->noof4wheelers));k++)
           {
               fscanf(fp,"%s %s",(ip->v[k]).name,(ip->v[k]).number);
               (ip->v[k])._2wheeler=false;
           }
           ip1=ip;
       }
       arr[j]=ip1;
   }

}






















pspot mapflat(level* ip,vehicle v)
{
    pspot ps1;
    int i;

    ps1.index=-1;
    if(v._2wheeler==true)
    {
        for(i=0;i<ip->noofcompactspots;i++)
        {
            if(ip->statuscompactspots[i]==0&&ip->mapcompact[i]==0)
            {
                ps1.index=i;
                ps1.compact=true;
                ps1.wingid=ip->wing;
                ip->mapcompact[i]=1;
                break;
            }
        }
        if(ps1.index==-1)
        {
            for(i=0;i<ip->nooflargespots;i++)
            {
                if(ip->statuslargespots[i]==0&&ip->maplarge[i]==0)
                {
                    ps1.index=i;
                    ps1.compact=false;
                    ps1.wingid=ip->wing;
                    ip->maplarge[i]=1;
                    break;
                }
            }
        }
        if(ps1.index==-1)
        {
            ps1=mapflat(ip->next,v);
            if(ps1.index==-1)
            {
                ps1=mapflat((ip->next)->next,v);
                if(ps1.index==-1)
                {
                    printf("NO VACANCY PRESENT\n");
                }
            }
        }
    }
    else
    {
       for(i=0;ip->nooflargespots;i++)
       {
           if((ip->statuslargespots[i]==0)&&(ip->maplarge[i]==0))
           {
               ps1.index=i;
               ps1.compact=false;
               ps1.wingid=ip->wing;
               ip->maplarge[i]=1;
               break;
           }
       }
       if(ps1.index==-1)
       {
           for(i=0;i<(ip->noofcompactspots)-1;i++)
           {
               if((ip->statuscompactspots[i]==0)&&(ip->statuscompactspots[i+1]==0)&&(ip->mapcompact[i]==0)&&(ip->mapcompact[i+1]==0))
               {
                   ps1.index=i;
                   ps1.compact=true;
                   ps1.wingid=ip->wing;
                   ip->mapcompact[i]=1;
                   ip->mapcompact[i+1]=1;
                   break;
               }
           }
           if(ps1.index==-1)
           {
               ps1=mapflat(ip->next,v);
               if(ps1.index==-1)
               {
                   ps1=mapflat((ip->next)->next,v);
                   if(ps1.index==-1)
                   {
                       printf("NO VACANCY\n");
                   }
               }
           }
       }



    }


return ps1;


}

void permanentparkingspot(flat* arr[],level* plot)
{
    flat* ip;
    int i,j,k;

    pspot ps;
    for(i=1;i<floorsinwing;i++)
    {
        ip=arr[i];
        while(ip!=NULL)
        {
            j=0;
            for( ;j<ip->noof2wheelers;j++)
            {
                ps=mapflat(plot,ip->v[j]);
                prr[pairscount].v=ip->v[j];
                prr[pairscount].ps=ps;
                pairscount++;
            }
            if(ip->noof4wheelers>0)
            {
                ps=mapflat(plot,ip->v[j]);
                prr[pairscount].v=ip->v[j];
                prr[pairscount].ps=ps;
                pairscount++;
                j++;
                for(k=1;k<ip->noof4wheelers;k++)
                {
                    ps=mapflat(plot->next,ip->v[j]);
                    prr[pairscount].v=ip->v[j];
                    prr[pairscount].ps=ps;
                   pairscount++;
                    j++;
                }
            }
            ip=ip->next;
        }
    }

}



















int binarysearch(int lo,int hi,char* key,couple arr[])
{
    if(lo>hi)
    {
        return -1;
    }
    else
    {
        int mid=(lo+hi)/2;
        if(strcmp(arr[mid].v.number,key)==0)
        {
            return mid;
        }
        else if(strcmp(arr[mid].v.number,key)>0)
        {
            return binarysearch(lo,mid-1,key,arr);
        }
        else
        {
            return binarysearch(mid+1,hi,key,arr);
        }

    }
}












void msort_vdr( couple city[],int lo, int hi)
{
    int mid;
    if(lo<hi)
    {
        mid=(lo+hi)/2;
        msort_vdr(city,lo,mid);
        msort_vdr(city,mid+1,hi);
        mergeself_vdr(city,lo,mid,hi);
    }
}

void mergeself_vdr( couple city[],int lo,int mid,int hi){
    couple temporary[pairscount];
    int i,j,k;
    i=lo;
    j=mid+1;
    k=lo;
    while((i<=mid)&&(j<=hi))
    {
        if(strcmp(city[i].v.number,city[j].v.number)>0)
        {
            temporary[k++]=city[j++];
        }
        else
        {
            temporary[k++]=city[i++];
        }
    }
    if(i<=mid)
    {
        while(i<=mid)
        {
            temporary[k++]=city[i++];
        }
    }
    else
    {
        while(j<=hi)
        {
            temporary[k++]=city[j++];
        }
    }
    for(i=lo;i<=hi;i++)
    {
        city[i]=temporary[i];
    }
}







guestvehicle* parkvehicle(char* vehiclenum,level* lotto,guestvehicle* vphead)
{
    pspot psv;
    int i,flag,k;
    flag=0;
    level* ip;
    ip=lotto;
    i=binarysearch(0,pairscount-1,vehiclenum,prr);
   // printf("%d bisearch index\n",i);
    if(i!=-1)
    {
        k=prr[i].ps.index;
        if(k==-1)
        {
            printf("no vacancy left\n");
            return vphead;
        }
      //  printf("%d\n parkingspot index in sorted array",k);
        while(ip->wing!=prr[i].ps.wingid)
        {
            ip=ip->next;
        }
        if((prr[i].v._2wheeler==false)&&(prr[i].ps.compact==true))
        {
            if((ip->statuscompactspots[k]==0)&&(ip->statuscompactspots[k+1]==0))
            {
                flag=0;
            }
            else
            {
                flag=1;
            }
        }
        else
        {
            if(prr[i].ps.compact==true)
            {
                if(ip->statuscompactspots[k]!=0)
                {
                    flag=1;
                }
            }
            else
            {
                if(ip->statuslargespots[k]!=0)
                {
                    flag=1;
                }
            }
        }
        if(flag==0)
        {
            if((prr[i].v._2wheeler==false)&&(prr[i].ps.compact==true))
            {
                ip->statuscompactspots[k]=1;
                ip->statuscompactspots[k+1]=1;
                printf("Compact spots indexed %d and %d allocated in parking level %c\n",k,k+1,ip->wing);

            }
            else
            {
                if(prr[i].ps.compact==true)
                {
                    ip->statuscompactspots[k]=1;
                    printf("compact spot indexed %d allocated in parking level %c\n",k,ip->wing);
                }
                else
                {
                    ip->statuslargespots[k]=1;
                    printf("large spot indexed %d allocated in parking level %c\n",k,ip->wing);

                }
            }
            return vphead;
        }
        else if(flag==1)
        {
            psv=mapflat(lotto,prr[i].v);
            k=psv.index;
            if(psv.index==-1)
            {
                printf("no vacancy\n");
            }
            else
            {
              while(ip->wing!=psv.wingid)
              {
                  ip=ip->next;
              }
               if((prr[i].v._2wheeler==false)&&(prr[i].ps.compact==true))
               {
                    ip->statuscompactspots[k]=1;
                    ip->statuscompactspots[k+1]=1;
                    printf("Compact spots indexed %d and %d allocated in parking level %c\n",k,k+1,ip->wing);

               }
               else
               {
                if(prr[i].ps.compact==true)
                {
                    ip->statuscompactspots[k]=1;
                    printf("compact spot indexed %d allocated in parking level %c\n",k,ip->wing);
                }
                else
                {
                    ip->statuslargespots[k]=1;
                    printf("large spot indexed %d allocated in parking level %c\n",k,ip->wing);

                }


               }

            }
            return vphead;

        }
    }
    else if(i==-1)
    {
        guestvehicle* vp;
        int m;
        vp=(guestvehicle*)malloc(sizeof(guestvehicle));
        printf("enter type of vehicle(2/4)wheeler\n");
        scanf("%d",&m);
        if(m==2)
        {
            vp->vh._2wheeler=true;
        }
        else if(m==4)
        {
            vp->vh._2wheeler=false;
        }
        printf("enter name of vehicle\n");
        scanf("%s",(vp->vh).name);
        printf("enter number of the vehicle\n");
        scanf("%s",(vp->vh).number);
        vp->next=NULL;
        time_t now;
        time(&now);
        strcpy(vp->day_time,ctime(&now));
        time_t t=time(NULL);
        struct tm tm=*localtime(&t);
        vp->year=tm.tm_year+1900;
        vp->day=tm.tm_mday;
        vp->mon=tm.tm_mon+1;
       // printf("ikada varak ok na\n");
        psv=mapflat(lotto,vp->vh);
        vp->psk=psv;
        //printf("ikada kuda ok na");
        k=psv.index;
            if(psv.index==-1)
            {
                printf("no vacancy\n");
            }
            else
            {
              while(ip->wing!=psv.wingid)
              {
                  ip=ip->next;
              }
               if((vp->vh._2wheeler==false)&&(psv.compact==true))
               {
                    ip->statuscompactspots[k]=1;
                    ip->statuscompactspots[k+1]=1;
                    printf("Compact spots indexed %d and %d allocated in parking level %c\n",k,k+1,ip->wing);

               }
               else
               {
                if(psv.compact==true)
                {
                    ip->statuscompactspots[k]=1;
                    printf("compact spot indexed %d allocated in parking level %c\n",k,ip->wing);
                }
                else
                {
                    ip->statuslargespots[k]=1;
                    printf("large spot indexed %d allocated in parking level %c\n",k,ip->wing);

                }


               }
            }
            if(vphead==NULL)
            {
                return vp;
            }
            else
            {
                guestvehicle* temp;
                temp=vphead;
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
                temp->next=vp;
                return vphead;

            }

    }


}
