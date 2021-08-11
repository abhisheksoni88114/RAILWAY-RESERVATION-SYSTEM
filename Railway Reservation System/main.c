#include <stdio.h>
#include <stdlib.h>
# include<string.h>
#include "conio2.h"
#include "rlyres.h"

int main()
{
    int choice, ticket_no;;
    add_trains();
    while(1)
    {
        choice = enterchoice();
        if (choice == 9)
        {
            textcolor(WHITE);
            exit(0);
        }

        switch(choice)
        {
            case 1:
                clrscr();
                view_trains();
                break;
            case 2:
                clrscr();
                ticket_no = book_ticket();
                if (ticket_no == -1)
                {
                    gotoxy(1, 21);
                    textcolor(LIGHTRED);
                    printf("Booking Failed!!");
                }
                else
                {
                    gotoxy(1, 21);
                    textcolor(LIGHTGREEN);
                    printf("Ticket Successfully Booked\nYour ticket no is %d", ticket_no);
                }
                textcolor(WHITE);
                gotoxy(2, 24);
                printf("Press any key to go back to the main screen");
                getch();
                clrscr();
                break;
            case 3:
                clrscr();
                ticket_no = accept_ticket_no();
                if (ticket_no != 0)
                    view_ticket(ticket_no);
                textcolor(LIGHTMAGENTA);
                gotoxy(2, 15);
                printf("Press any key to go back to the main screen");
                getch();
                clrscr();
                break;
            case 4:
                clrscr();
                get_ticket_no();
                textcolor(LIGHTMAGENTA);
                gotoxy(2, 15);
                printf("Press any key to go back to the main screen");
                getch();
                clrscr();
                break;
            case 5:
                clrscr();
                int y_pos;
                y_pos = view_all_bookings();
                textcolor(LIGHTMAGENTA);
                y_pos = y_pos+3;
                gotoxy(2, y_pos);
                printf("Press any key to go back to the main screen");
                getch();
                clrscr();
                break;
            case 6:
                //view_booking();
                break;
            case 7:
                //cancel_ticket();
                break;
            case 8:
                //cancel_train();
                break;
            default:
                textcolor(LIGHTRED);
                printf("\n\tWrong choice!! Try again");
                getch();
                clrscr();
        }
    }
    return 0;
}
