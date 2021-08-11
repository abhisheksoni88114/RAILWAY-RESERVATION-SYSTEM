#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"

void overview()
{
    int i;
    textcolor(YELLOW);
    gotoxy(72, 2);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for (i=1; i<=168; i++)
        printf("~");
}

int enterchoice()
{
    int choice;
    overview();
    printf("\n\nSelect an option");
    printf("\n\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");
    printf("\n\nEnter choice: ");
    scanf("%d", &choice);
    return choice;
}

void add_trains()
{
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\alltrains.dat", "rb");
    if (fp == NULL)
    {
        Train alltrains[4] = {
            {"123","BPL","GWA",2100,1500},
            {"546","BPL","DEL",3500,2240},
            {"345","HBJ","AGR",1560,1135},
            {"896","HBJ","MUM",4500,3360},
        };
        fp = fopen("G:\\C project 2020\\Railway Reservation System\\alltrains.dat", "wb");
        fwrite(&alltrains, 4*sizeof(Train), 1, fp);
        printf("File saved successfully!\n");
        fclose(fp);
    }
    else{
        printf("File already present!!\n");
        fclose(fp);
    }
}

void view_trains()
{
    int i;
    gotoxy(1, 2);
    printf("TRAIN NO\t\tFROM\t\tTO\t\tFIRST AC FARE\t\tSECOND AC FARE\n");
    for (i=1; i<=168; i++)
        printf("-");
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\alltrains.dat", "rb");
    Train tr;
    while (fread(&tr, sizeof(tr), 1, fp) == 1)
    {
        //gotoxy(45, j);
        printf("\n%s\t\t\t%s\t\t%s\t\t%d\t\t\t%d", tr.train_no, tr.from, tr.to, tr.fac_fare, tr.sac_fare);
        //printf("\n");
    }
    fclose(fp);
    printf("\n\n\n\n");
    textcolor(WHITE);
    printf("Press any key to go back to the main screen");
    getch();
    clrscr();
}

int check_train_no(char *trainno)
{
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\alltrains.dat", "rb");
    Train tr;
    while(fread(&tr, sizeof(tr), 1, fp) == 1)
    {
        if (strcmp(trainno, tr.train_no) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int check_mob_no(char *mobno)
{
    int i;
    if (strlen(mobno) != 10)
        return 0;
    for (i=0; i<10; i++)
    {
        if(isdigit(*(mobno+i)) == 0)
            return 0;
    }
    return 1;
}

Passenger* get_passenger_details()
{
    gotoxy(90, 1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1, 1);
    textcolor(YELLOW);
    static Passenger pn;
    printf("Enter passenger name: ");
    fflush(stdin);
    fgets(pn.p_name, 20, stdin);
    char *pos;
    pos = strchr(pn.p_name, '\n');
    *pos = '\0';
    if (strcmp(pn.p_name, "0") == 0)
    {
        gotoxy(1, 19);
        textcolor(LIGHTRED);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    int valid;
    printf("Enter gender(M/F): ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%c", &pn.gender);
        printf("%c", pn.gender);
        if (pn.gender == '0')
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (pn.gender != 'M' && pn.gender != 'F')
        {
            valid = 0;
            gotoxy(1, 25);
            textcolor(LIGHTRED);
            printf("Error! Gender should be M or F (uppercase)");
            getch();
            gotoxy(20, 2);
            printf("\t");
            gotoxy(20, 2);
            textcolor(YELLOW);
        }
    }while (valid == 0);      // OR while (pn.gender != "M" && pn.gender != "F");
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1, 3);
    printf("Enter Train no: ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%s", pn.train_no);
        if (strcmp(pn.train_no, "0") == 0)
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (check_train_no(pn.train_no) == 0)
        {
            valid = 0;
            gotoxy(1, 25);
            textcolor(LIGHTRED);
            printf("Error! Invalid Train No");
            getch();
            gotoxy(17, 3);
            printf("\t\t\t\t\t");
            gotoxy(17, 3);
            textcolor(YELLOW);
        }
    }while (valid == 0);
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1, 4);
    printf("Enter travelling class (First AC-F, Second AC-S): ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%c", &pn.p_class);
        if (pn.p_class == '0')
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (pn.p_class != 'F' && pn.p_class != 'S')
        {
            valid = 0;
            gotoxy(1, 25);
            textcolor(LIGHTRED);
            printf("Error! Travelling Class should be F or S (uppercase)");
            getch();
            gotoxy(51, 4);
            printf("\t");
            gotoxy(51, 4);
            textcolor(YELLOW);
        }
    }while (valid == 0);
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1, 5);
    printf("Enter Address: ");
    fflush(stdin);
    fgets(pn.address, 30, stdin);
    pos = strchr(pn.address, '\n');
    *pos = '\0';
    if (strcmp(pn.address, "0") == 0)
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
    gotoxy(1, 6);
    printf("Enter age: ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%d", &pn.age);
        if (pn.age == 0)
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (pn.age < 0)
        {
            valid = 0;
            gotoxy(1, 25);
            textcolor(LIGHTRED);
            printf("Error! Age should be positive");
            getch();
            gotoxy(12, 6);
            printf("\t\t\t\t");
            gotoxy(12, 6);
            textcolor(YELLOW);
        }
    }while (valid == 0);      // OR while (pn.gender != "M" && pn.gender != "F");
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1, 7);
    printf("Enter mobile number: ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%s", pn.mob_no);
        if (strcmp(pn.mob_no, "0") == 0)
        {
            gotoxy(1, 19);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (check_mob_no(pn.mob_no) == 0)
        {
            valid = 0;
            gotoxy(1, 25);
            textcolor(LIGHTRED);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(22, 7);
            printf("\t\t\t\t\t");
            textcolor(YELLOW);
            gotoxy(22, 7);
        }
    }while (valid == 0);
    gotoxy(1, 25);
    printf("\t\t\t\t\t\t\t");
    return &pn;
}

int get_booked_ticket_count(char *trainno, char pclass)
{
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "rb");
    if (fp == NULL)
        return 0;
    Passenger pn;
    int count=0;
    while (fread(&pn, sizeof(pn), 1, fp) == 1)
    {
        if ((strcmp(pn.train_no, trainno) == 0) && (pclass == pn.p_class))
            count++;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "rb");
    if (fp == NULL)
        return 0;
    Passenger pn;
    fseek(fp, -1*(sizeof(pn)), SEEK_END);
    fread(&pn, sizeof(pn), 1, fp);
    fclose(fp);
    return pn.ticketno;
}

int book_ticket()
{
    Passenger *pn;
    pn = get_passenger_details();
    if (pn == NULL)
        return -1;
    int count = get_booked_ticket_count(pn->train_no, pn->p_class);
    if (count == 2)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!!", pn->train_no, pn->p_class);
        return -1;
    }
    pn->ticketno = last_ticket_no()+1;
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "ab");
    if (fp == NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened.");
        return -1;
    }
    fwrite(pn, sizeof(*pn), 1, fp);
    fclose(fp);
    return pn->ticketno;
}

int accept_ticket_no()
{
    printf("Enter ticket no: ");
    int valid, ticket_no;
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%d", &ticket_no);
        if (ticket_no == 0)
        {
            gotoxy(1, 10);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1, 10);
            textcolor(LIGHTRED);
            printf("Cancelling input....");
            getch();
            textcolor(YELLOW);
            return 0;
        }
        if (ticket_no < 0)
        {
            valid = 0;
            gotoxy(1, 10);
            textcolor(LIGHTRED);
            printf("Error! ticket number should be positive!");
            getch();
            gotoxy(18, 1);
            printf("\t\t\t\t");
            gotoxy(18, 1);
            textcolor(YELLOW);
        }
    }while (valid == 0);
    gotoxy(1, 10);
    printf("\t\t\t\t\t\t\t");
    return ticket_no;
}

void view_ticket(int ticket_no)
{
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "rb");
    if (fp == NULL)
    {
        gotoxy(1, 10);
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return;
    }
    Passenger pn;
    int found = 0;
    while (fread(&pn, sizeof(pn), 1, fp) == 1)
    {
        if (ticket_no == pn.ticketno)
        {
            found = 1;
            gotoxy(1, 3);
            printf("\nName: %s\nGender: %c\nTrain no: %s\nClass: %c\nAddress: %s\nAge: %d\nMobile no: %s\nTicket no: %d", pn.p_name, pn.gender, pn.train_no, pn.p_class, pn.address, pn.age, pn.mob_no, pn.ticketno);
            break;
        }
    }
    if (!found)
    {
        gotoxy(1, 10);
        textcolor(LIGHTRED);
        printf("No details of ticket no %d found...", ticket_no);
    }
    fclose(fp);
}

void get_ticket_no()
{
    int i, valid;
    Passenger pn1, pn2;
    overview();
    printf("\n\nEnter mobile number: ");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%s", pn1.mob_no);
        if (strcmp(pn1.mob_no, "0") == 0)
        {
            gotoxy(1, 13);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1, 13);
            textcolor(LIGHTRED);
            printf("Searching Cancelled!!");
            getch();
            textcolor(YELLOW);
            return;
        }
        if (check_mob_no(pn1.mob_no) == 0)
        {
            valid = 0;
            gotoxy(1, 13);
            textcolor(LIGHTRED);
            printf("ERROR! Invalid Mobile No");
            getch();
            gotoxy(22, 6);
            printf("\t\t\t\t\t");
            textcolor(YELLOW);
            gotoxy(22, 6);
        }
    }while (valid == 0);
    gotoxy(1, 13);
    printf("\t\t\t\t\t\t\t");
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "rb");
    if (fp == NULL)
    {
        gotoxy(1, 13);
        textcolor(LIGHTRED);
        printf("No bookings done yet!!!");
        return;
    }
    valid = 0;
    i = 9;
    int ticket_count = 1;
    while(fread(&pn2, sizeof(pn2), 1, fp) == 1)
    {
        if (strcmp(pn1.mob_no, pn2.mob_no) == 0)
        {
            valid = 1;
            gotoxy(1, i);
            printf("TICKET NUMBER %d: %d", ticket_count, pn2.ticketno);
            i++;
            ticket_count++;
        }
    }
    if (!valid)
    {
        gotoxy(1, 13);
        textcolor(LIGHTRED);
        printf("!!No ticket found related to mobile number %s ...", pn1.mob_no);
    }
    fclose(fp);
}

int view_all_bookings()
{
    overview();
    FILE *fp = fopen("G:\\C project 2020\\Railway Reservation System\\allbookings.dat", "rb");
    if (fp == NULL)
    {
        gotoxy(1, 10);
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return 13;
    }
    Passenger pn;
    int y_pos = 6;
    while (fread(&pn, sizeof(pn), 1, fp) == 1)
    {
            gotoxy(1, y_pos);
            printf("\nName: %s\nGender: %c\nTrain no: %s\nClass: %c\nAddress: %s\nAge: %d\nMobile no: %s\nTicket no: %d", pn.p_name, pn.gender, pn.train_no, pn.p_class, pn.address, pn.age, pn.mob_no, pn.ticketno);
            y_pos = y_pos+10;
    }
    fclose(fp);
    return y_pos;
}
