#ifndef USER_FUNKCIJE_H_INCLUDED
#define USER_FUNKCIJE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

typedef struct event
{
    char name[100];
    char location[100];
    char category[100];
    char day[3];
    char month[3];
    char year[5];
    char time[20];
    char description[200];
} EVENT;

typedef struct node
{
    EVENT info;
    struct node* next;
} NODE;

void print_hello(); //Ispis pozdravne poruke
void pull_from_folder(NODE** head); //skida sadrzaj datoteke sa dogadjajima u listu
void add_event(NODE** head, EVENT event); //Dodaje dogadjaj u listu
void print_today_events(NODE* list); //Ispisuje danasnje dogadjaje
void print_future_events(NODE* list); //Ispisuje buduce dogadjaje
void print_past_events(NODE* list); //Ispisuje prosle dogadjaje
void print_event_from_category(NODE* list); //Ispisuje dogadjaje iz odabrane kategorije
int print_all_events(NODE* list); //Ispisuje sve dogadjaje
int print_all_events_info(NODE* list); //Ispisuje sve info o svim dogadjajima
void print_event_info(NODE*); //Ispisuje sve informacije o jednom dogadjaju
NODE* choose_event(NODE* list, int n);
void choose_category(FILE* fcategories, char*); //Izbor kategorije
void add_comment(char*);
void print_comments(char*);
void quiz(); //Kviz
void delete_bsn(char* s);
int choose_from_menu(int count);
int list_is_empty(NODE* list);

#endif // USER_FUNKCIJE_H_INCLUDED
