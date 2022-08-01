/* HEADER FILES */

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define ROOM_BVB 365
#define ROOM_LBS 260
#define ROOM_MG 250
#define ROOM_AP 220

/* SET CURSOR */

COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int i;

/* Structure for FILE to store details of hostellite */

struct student
{
    char name[20];
    char USN [5];
    int roomNo;
}s;

/* Structure for SLL to print sorted details */

typedef struct node
{
    char name[20];
    char USN [5];
    int roomNo;
    struct node *next;
}NODE;

/* Structure for SLL to input Entry and Exit Records */

typedef struct hostellite
{
    char name[20];
    int roomNo;
    char status[5];
    struct time
    {
        int hour;
        int min;
    }t;
    struct hostellite *next;
}Node;

/* Structure for FILE to store Entry and Exit Records */

struct hostelliteF
{
    char name[20];
    int roomNo;
    char status[5];
    struct timeF
    {
        int hour;
        int min;
    }t;
}h;

/* Function to insert at the end of SLL */

Node * ins_last(Node *first)
{
    system("cls");
    gotoxy(40,4);
    printf("Enter Details to Enter/Exit");

Node *newnode,*temp;
newnode=(Node*)malloc(sizeof(Node));

gotoxy(35,6);
printf("Enter student name: ");
gotoxy(55,6);
scanf("%s",newnode->name);
gotoxy(35,8);
printf("Enter RoomNo: ");
gotoxy(49,8);
scanf("%d",&newnode->roomNo);
gotoxy(35,10);
printf("Enter status(Entry/Exit): ");
gotoxy(61,10);
scanf("%s",newnode->status);
gotoxy(35,12);
printf("Enter time (hr:mm): ");
gotoxy(56,12);
scanf("%d:%d",&newnode->t.hour,&newnode->t.min);
newnode->next=NULL;

if(first==NULL)
first=newnode;
else
{
temp=first;
while(temp->next!=NULL)
    temp=temp->next;
temp->next=newnode;
}
gotoxy(35,14);
printf("Record successfully updated!");
getch();
return first;
}

/* Function to enter the Entry/Exit records in SLL and then store it in FILE */

void EntryExitRecords(FILE *fp,FILE *record)
{
    Node *entry=NULL,*exit=NULL,*temp;
    int choice,flag1=0,flag2=0;
    char name[20];

    while(flag1!=1)
    {
        system("cls");
        gotoxy(35,5);
        printf("1 : Update Exit Record ");
        gotoxy(35,7);
        printf("2 : Update Entry Record ");
        gotoxy(35,9);
        printf("3 : Exit loop");
        gotoxy(35,11);
        printf("Enter your choice->");
        gotoxy(55,11);
        scanf("%d",&choice);

        switch(choice)
        {

    case 1:
            system("cls");

            gotoxy(35,6);
            printf("Enter student's name: ");
            gotoxy(57,6);
            scanf("%s",name);
            rewind(fp);
            while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
            {
                if(strcmp(s.name,name)==0)
                {
                    flag2=1;
                    exit=ins_last(exit);
                    break;
                }
            }
            if(flag2==0)
            {
                gotoxy(35,9);
                printf("Room has not been allocated to %s",name);
                getch();
            }
            flag2=0;
            break;
        case 2:
            system("cls");

            gotoxy(35,6);
            printf("Enter student's name: ");
            gotoxy(57,6);
            scanf("%s",name);
            rewind(fp);
            while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
            {
                if(strcmp(s.name,name)==0)
                {
                    flag2=1;
                    break;
                }
            }
            if(flag2==0)
            {
                gotoxy(35,9);
                printf("Student doesn't belong to hostel");
                getch();
            }
            else
            {
                temp=exit;
                while(temp!=NULL)
                {
                    if(strcmp(temp->name,name)==0)
                    {
                        flag2=2;
                        entry=ins_last(entry);
                        break;
                    }
                }
                if(flag2==1)
                {
                    gotoxy(35,9);
                    printf("ERROR: Student yet to exit hostel");
                    getch();
                }
            }
            flag2=0;
            break;
        case 3:
            flag1=1;
            break;
        default:
            system("cls");
            gotoxy(35,9);
            printf("Invalid Input");
        }
    }
    while(entry!=NULL)
    {
        fprintf(record,"%s\t%d\t%s\t%02d:%02d\n",entry->name,entry->roomNo,entry->status,entry->t.hour,entry->t.min);
        entry=entry->next;
    }
    while(exit!=NULL)
    {
        fprintf(record,"%s\t%d\t%s\t%02d:%02d\n",exit->name,exit->roomNo,exit->status,exit->t.hour,exit->t.min);
        exit=exit->next;
    }
}

/* Function to display the Entry and Exit Records from FILE */

void displayEntryExitRecords(FILE *fp)
{
    system("cls");
    int flag=0,y=4;

            while(fscanf(fp,"%s%d%s%d:%d",h.name,&h.roomNo,h.status,&h.t.hour,&h.t.min)!=EOF)
            {
                if(flag==0)
                {
                    gotoxy(35,y);
                    printf("Name \t RoomNo \t Status \t Timing");
                    flag=1;
                }
                y++;
                gotoxy(35,y);
                printf("%s  \t  %d  \t\t  %s  \t  %02d:%02d",h.name,h.roomNo,h.status,h.t.hour,h.t.min);
            }
            if(flag==0)
            {
                gotoxy(35,4);
                printf("No Entry/Exit has been recorded yet !!");
            }
            getch();
}

/* Welcome Screen */

void welcome()
{
    int i;
    char message[15]={"Welcome to all"};
    gotoxy(35,8);
    for(i=1;i<34;i++)
    {
        printf("\xB2");
        Sleep(20);
    }
    gotoxy(35,9);
    printf("\xB2\xB2");
    gotoxy(66,9);
    printf("\xB2\xB2");
    gotoxy(35,10);
    for(i=1;i<10;i++)
    {
        printf("*");
        Sleep(40);
    }
    for(i=0;i<15;i++)
    {
        printf("%c",message[i]);
        Sleep(50);
    }
    for(i=1;i<10;i++)
    {
       printf("*");
        Sleep(50);
    }
    gotoxy(35,11);
    printf("\xB2\xB2");
    gotoxy(66,11);
    printf("\xB2\xB2");
    gotoxy(35,12);
    for(i=1;i<34;i++)
    {
        printf("\xB2");
        Sleep(25);
    }
    gotoxy(38,14);
    printf("Press any Key to continue->\n");
    gotoxy(65,14);
    getch();
}

/* Display the names of Hostels */

void hostelNames()
{
    system("cls");
    int i;
    gotoxy(38,4);
    for(i=1;i<20;i++)
        printf("\xB2");
    for(i=5;i<=15;i++)
    {
        gotoxy(38,i);
        printf("\xB2");
    }
    for(i=5;i<=15;i++)
    {
        gotoxy(56,i);
        printf("\xB2");
    }
    gotoxy(41,6);
    printf("1 : BVB BLOCK ");
    gotoxy(41,8);
    printf("2 : LBS BLOCK ");
    gotoxy(41,10);
    printf("3 : MG BLOCK ");
    gotoxy(41,12);
    printf("4 : AP BLOCK ");
    gotoxy(41,14);
    printf("5 : EXIT ");
    gotoxy(38,16);
    for(i=1;i<20;i++)
        printf("\xB2");
}

/* Display the info for the users choice */

void info()
{
    system("cls");
    gotoxy(41,7);
    printf("1 : Room Allocation ");
    gotoxy(41,9);
    printf("2 : Search Student ");
    gotoxy(41,11);
    printf("3 : Deallocate Room ");
    gotoxy(41,13);
    printf("4 : Print details of hostelers ");
    gotoxy(41,15);
    printf("5 : Print sorted details ");
    gotoxy(41,17);
    printf("6 : Entry Exit Records ");
    gotoxy(41,19);
    printf("7 : Display Entry Exit Records ");
    gotoxy(41,21);
    printf("8 : Clear Entry Exit Records ");
    gotoxy(41,23);
    printf("9 : Exit ");
}

/* Function to store the student's details */

void updateRecord(FILE *fp,int MaxRooms)
{
    system("cls");

    int roomNo;
    gotoxy(35,4);
    printf("Enter room number : ");
    gotoxy(55,4);
    scanf("%d",&roomNo);
    if(roomNo>MaxRooms){
    gotoxy(35,6);
    printf("Room Number exceeded total room number !! TRY AGAIN ");
    getch();
            return ;
            }
    else{
            while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
            {
                if(roomNo==s.roomNo)
                {
                    gotoxy(35,6);
                    printf("Room is full.Try another room.");
                    getch();
                    return;
                }
            }
            }
                    s.roomNo=roomNo;
                    gotoxy(35,6);
                    printf("Enter student's name: ");
                    gotoxy(58,6);
                    scanf("%s",s.name);
                    gotoxy(35,7);
                    printf("Enter student's USN: ");
                    gotoxy(57,7);
                    scanf("%s",s.USN);
                    fprintf(fp,"%s \t %s \t %d \n",s.name,s.USN,s.roomNo);
}

/* Function to search for a specific student in the Hostel */

void search(FILE *fp)
{
    system("cls");
    int flag=0;
    char name[20];
    gotoxy(35,4);
    printf("Enter the name of student: ");
    gotoxy(62,4);
    scanf("%s",name);
            while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
            {
                if(strcmp(name,s.name)==0)
                {
                    flag=1;
                    gotoxy(35,6);
                    printf("Student's name : %s",s.name);
                    gotoxy(35,8);
                    printf("USN : %s",s.USN);
                    gotoxy(35,10);
                    printf("Room Number : %d",s.roomNo);
                    getch();
                }
            }
            if(flag==0)
            {
                gotoxy(35,6);
                printf("Student not Found!!");
                getch();
            }
}

/* Function to display students details */

void displayRecord(FILE *fp)
{
    system("cls");
    int flag2=0,y=4;

            while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
            {
                if(flag2==0)
                {
                    gotoxy(35,y);
                    printf("Name \t USN \t RoomNumber");
                    flag2=1;
                }
                y++;
                gotoxy(35,y);
                printf("%s  \t  %s  \t  %d",s.name,s.USN,s.roomNo);
            }
            if(flag2==0)
            {
                gotoxy(35,4);
                printf("Hostel is empty");
            }
            getch();
}

/* Function to print sorted student details using Ordered List */

void displaySort(FILE *fp)
{
    system("cls");
    int y=7;
    NODE *first=NULL;
    NODE *newnode,*temp,*prev;

while(fscanf(fp,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
{
newnode=(NODE*)malloc(sizeof(NODE));
newnode->roomNo=s.roomNo;
strcpy(newnode->name,s.name);
strcpy(newnode->USN,s.USN);
if(first==NULL || s.roomNo<first->roomNo)
{
 newnode->next=first;
 first=newnode;
}
else
{
 temp=first;
 while(temp!=NULL && s.roomNo>temp->roomNo)
 {
 prev=temp;
 temp=temp->next;
 }
 if(temp==NULL || s.roomNo!=temp->roomNo)
 {
 prev->next=newnode;
 newnode->next=temp;
 }}}
 if(first==NULL)
 {
     gotoxy(35,5);
     printf("File is Empty");
 }
 else
 {
gotoxy(35,5);
printf("Name \tUSN\tRoomNo");
while(first!=NULL)
{
    gotoxy(35,y);
    printf("%s\t%s\t%d",first->name,first->USN,first->roomNo);
    first=first->next;
    y++;
}}
getch();
}

/* MAIN Function*/

int main()
{
    FILE *bvb,*lbs,*mgb,*apb;
    FILE *recordB,*recordL,*recordM,*recordA;
    FILE *temp;
    int choice,flag=0;
    welcome();
    while(1)
    {
            hostelNames();

        gotoxy(38,18);
    printf("Enter your choice : ");
    switch(getch())
    {
    case '1':
        system("cls");
        char message[]={"**********Welcome to BVB**********"};
        gotoxy(35,4);
        for(i=0;i<35;i++)
        {
            printf("%c",message[i]);
            Sleep(40);
        }
        Sleep(1500);
        while(1){
                info();
                gotoxy(41,25);
        printf("Enter your Choice");
        gotoxy(59,25);
        scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    bvb=fopen("BVB","a+");
                    updateRecord(bvb,ROOM_BVB);
                    fclose(bvb);
                    break;
                case 2:
                    bvb=fopen("BVB","r");
                    search(bvb);
                    fclose(bvb);
                    break;
                case 3:
                     /* To delete a specific student's details from FILE */
                    system("cls");
                    bvb=fopen("BVB","r");
                    temp=fopen("Temp","a+");
                    char Sname[20];
                    gotoxy(35,4);
                    printf("Enter the name of student:");
                    gotoxy(62,4);
                    scanf("%s",Sname);
                    while(fscanf(bvb,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
                    {
                        flag=1;
                        if(strcmp(s.name,Sname)!=0)
                        fprintf(temp,"%s \t %s \t %d \n",s.name,s.USN,s.roomNo);
                    }
                    if(flag==0)
                    {
                        gotoxy(35,8);
                        printf("Entered name incorrect !!");
                        getch();
                    }
                    fclose(temp);
                    fclose(bvb);
                    remove("BVB");
                    rename("Temp","BVB");
                    break;
                case 4:
                    bvb=fopen("BVB","r");
                    displayRecord(bvb);
                    fclose(bvb);
                    break;
                case 5:
                    bvb=fopen("BVB","r");
                    displaySort(bvb);
                    fclose(bvb);
                    break;
                case 6:
                    bvb=fopen("BVB","r");
                    recordB=fopen("BVBrecord","a+");
                    EntryExitRecords(bvb,recordB);
                    fclose(bvb);
                    fclose(recordB);
                    break;
                case 7:
                    recordB=fopen("BVBrecord","r");
                    displayEntryExitRecords(recordB);
                    fclose(recordB);
                    break;
                case 8:
                    remove("BVBrecord");
                    break;
                default:
                    break;
            }
            if(choice>8)
                break;
        }
        break;
        case '2':
        system("cls");
        char message2[]={"**********Welcome to LBS**********"};
        gotoxy(35,4);
        for(i=0;i<35;i++)
        {
            printf("%c",message2[i]);
            Sleep(40);
        }
        Sleep(1500);
        while(1){
                info();
                gotoxy(41,25);
        printf("Enter your Choice");
        gotoxy(59,25);
        scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    lbs=fopen("LBS","a+");
                    updateRecord(lbs,ROOM_LBS);
                    fclose(lbs);
                    break;
                case 2:
                    lbs=fopen("LBS","r");
                    search(lbs);
                    fclose(lbs);
                    break;
                case 3:
                     /* To delete a specific student's details from FILE */
                    system("cls");
                    lbs=fopen("LBS","r");
                    temp=fopen("Temp","a+");
                    char Sname[20];
                    gotoxy(35,4);
                    printf("Enter the name of student:");
                    gotoxy(62,4);
                    scanf("%s",Sname);
                    while(fscanf(bvb,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
                    {
                        flag=1;
                        if(strcmp(s.name,Sname)!=0)
                        fprintf(temp,"%s \t %s \t %d \n",s.name,s.USN,s.roomNo);
                    }
                    if(flag==0)
                    {
                        gotoxy(35,8);
                        printf("Entered name incorrect !!");
                        getch();
                    }
                    fclose(temp);
                    fclose(lbs);
                    remove("LBS");
                    rename("Temp","LBS");
                    break;
                case 4:
                    lbs=fopen("LBS","r");
                    displayRecord(lbs);
                    fclose(lbs);
                    break;
                case 5:
                    lbs=fopen("LBS","r");
                    displaySort(lbs);
                    fclose(lbs);
                break;
                case 6:
                    lbs=fopen("LBS","r");
                    recordL=fopen("LBSrecord","a+");
                    EntryExitRecords(lbs,recordL);
                    fclose(lbs);
                    fclose(recordL);
                    break;
                case 7:
                    recordL=fopen("LBSrecord","r");
                    displayEntryExitRecords(recordL);
                    fclose(recordL);
                    break;
                case 8:
                    remove("LBSrecord");
                    break;
                default:
                    break;
            }
            if(choice>8)
                break;
        }
        break;
    case '3':
        system("cls");
        char message3[]={"**********Welcome to MGB**********"};
        gotoxy(35,4);
        for(i=0;i<35;i++)
        {
            printf("%c",message3[i]);
            Sleep(40);
        }
        Sleep(1500);
        while(1){
                info();
                gotoxy(41,25);
        printf("Enter your Choice");
        gotoxy(59,25);
        scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    mgb=fopen("MGB","a+");
                    updateRecord(mgb,ROOM_MG);
                    fclose(mgb);
                    break;
                case 2:
                    mgb=fopen("MGB","r");
                    search(mgb);
                    fclose(mgb);
                    break;
                case 3:
                     /* To delete a specific student's details from FILE */
                    system("cls");
                    mgb=fopen("MGB","r");
                    temp=fopen("Temp","a+");
                    char Sname[20];
                    gotoxy(35,4);
                    printf("Enter the name of student:");
                    gotoxy(62,4);
                    scanf("%s",Sname);
                     while(fscanf(bvb,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
                    {
                        flag=1;
                        if(strcmp(s.name,Sname)!=0)
                        fprintf(temp,"%s \t %s \t %d \n",s.name,s.USN,s.roomNo);
                    }
                    if(flag==0)
                    {
                        gotoxy(35,8);
                        printf("Entered name incorrect !!");
                        getch();
                    }
                    fclose(temp);
                    fclose(mgb);
                    remove("MGB");
                    rename("Temp","MGB");
                    break;
                case 4:
                    mgb=fopen("MGB","r");
                    displayRecord(mgb);
                    fclose(mgb);
                    break;
                case 5:
                    mgb=fopen("MGB","r");
                    displaySort(mgb);
                    fclose(mgb);
               break;
                case 6:
                    mgb=fopen("MGB","r");
                    recordM=fopen("MGBrecord","a+");
                    EntryExitRecords(mgb,recordM);
                    fclose(mgb);
                    fclose(recordM);
                    break;
                case 7:
                    recordM=fopen("MGBrecord","r");
                    displayEntryExitRecords(recordM);
                    fclose(recordM);
                    break;
                case 8:
                    remove("MGBrecord");
                    break;
                default:
                    break;
            }
            if(choice>8)
                break;
        }
        break;
        case '4':
        system("cls");
        char message4[]={"**********Welcome to APB**********"};
        gotoxy(35,4);
        for(i=0;i<35;i++)
        {
            printf("%c",message4[i]);
            Sleep(40);
        }
        Sleep(1500);
        while(1){
                info();
                gotoxy(41,25);
        printf("Enter your Choice");
        gotoxy(59,25);
        scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    apb=fopen("APB","a+");
                    updateRecord(apb,ROOM_AP);
                    fclose(apb);
                    break;
                case 2:
                    apb=fopen("APB","r");
                    search(apb);
                    fclose(apb);
                    break;
                case 3:
                     /* To delete a specific student's details from FILE */
                    system("cls");
                    apb=fopen("APB","r");
                    temp=fopen("Temp","a+");
                    char Sname[20];
                    gotoxy(35,4);
                    printf("Enter the name of student:");
                    gotoxy(62,4);
                    scanf("%s",Sname);
                    while(fscanf(bvb,"%s%s%d",s.name,s.USN,&s.roomNo)!=EOF)
                    {
                        flag=1;
                        if(strcmp(s.name,Sname)!=0)
                        fprintf(temp,"%s \t %s \t %d \n",s.name,s.USN,s.roomNo);
                    }
                    if(flag==0)
                    {
                        gotoxy(35,8);
                        printf("Entered name incorrect !!");
                        getch();
                    }
                    fclose(temp);
                    fclose(apb);
                    remove("APB");
                    rename("Temp","APB");
                    break;
                case 4:
                    apb=fopen("APB","r");
                    displayRecord(apb);
                    fclose(apb);
                    break;
                case 5:
                    apb=fopen("APB","r");
                    displaySort(apb);
                    fclose(apb);
               break;
                case 6:
                    apb=fopen("APB","r");
                    recordA=fopen("APBrecord","a+");
                    EntryExitRecords(apb,recordA);
                    fclose(apb);
                    fclose(recordA);
                    break;
                case 7:
                    recordA=fopen("APBrecord","r");
                    displayEntryExitRecords(recordA);
                    fclose(recordA);
                    break;
                case 8:
                    remove("APBrecord");
                    break;
                default:
                    break;
            }
            if(choice>8)
                break;
        }
        break;
        case '5': system("cls");
        gotoxy(39,10);
        printf("Exiting in->");
        for(i=3;i>=0;i--)
        {
            gotoxy(53,10);
            printf("%d",i);
            Sleep(1000);
        }
            exit(0);
            break;
    }}

    return 0;
}
