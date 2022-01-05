#ifndef PARKINGLOT_H_INCLUDED
#define PARKINGLOT_H_INCLUDED
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define sz 100
#define floorsinwing 2
#define flatsperfloor 2
#define max_no_of_vehicles 5
int pairscount;
typedef struct level
{
    char wing;
    int noofcompactspots;
    int nooflargespots;
    int statuscompactspots[sz];
    int mapcompact[sz];
    int maplarge[sz];
    int statuslargespots[sz];
    struct level* next;
}level;
typedef struct vehicle
{
    char number[20];
    char name[20];
    bool _2wheeler;
}vehicle;
typedef struct pspot
{
    char wingid;
    bool compact;
    int index;
}pspot;
typedef struct flat
{
    char wing;
    int flatid;
    int noof2wheelers;
    int noof4wheelers;
    struct flat* next;
    vehicle v[max_no_of_vehicles];
}flat;
typedef struct couple
{
    vehicle v;
    pspot ps;
}couple;
typedef struct guestvehicle
{

    char day_time[40];
    pspot psk;
    vehicle vh;
    int day;
    int mon;
    int year;
    struct guestvehicle* next;
}guestvehicle;
couple prr[flatsperfloor*max_no_of_vehicles*floorsinwing*3];
void permanentparkingspot(flat* arr[],level* plot);
pspot mapflat(level*ip,vehicle v);
void allocate_flats(flat* arr[],char ch,FILE* fp);
void msort_vdr( couple city[],int lo, int hi);
void mergeself_vdr( couple city[],int lo,int mid,int hi);
int binarysearch(int lo,int hi,char* key,couple arr[]);
guestvehicle* parkvehicle(char* vehiclenum,level* lotto,guestvehicle* vphead);


#endif // PARKINGLOT_H_INCLUDED
