#ifndef FUNKCIJE_H_INCLUDED
#define FUNKCIJE_H_INCLUDED
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct event{
	char name[100];
	char location[100];
	char category[100];
	char day[3];
	char month[3];
	char year[5];
	char time[20];
	char description[200];
}EVENT;

typedef struct node {
	EVENT info;
	struct node* next;
}NODE;

void read_user_info(char *, char*);
char* enter_password(char *);
void login(); //F-ja za prijavu
int choose_from_menu(int); //Zasticen izbor iz menija
void make_predef_cat(); //Kreira predefinisane kategorije
void print_categories(); //Ispisuje sve kategorije
void add_category(); //Dodaje novu kategoriju
void delete_category(); //Brise zeljenu kategoriju
void print_comments(char*); //Ispisuje sve komentare
void add_comment(char*); //Dodaje komentar na dogadjaj
void delete_comment(char*); //Brise zeljeni komentar
void pull_from_folder(NODE**); //skida sadrzaj datoteke sa dogadjajima u listu
void push_to_folder(NODE*); //vraca listu sa dogadjajima u datoteku
void choose_category(FILE* fcategories, char*); //bira kategoriju dogadjaja
void add_event(NODE**, EVENT); //dodaje novi dogadjaj
EVENT event_info(); //unos informacija o dogadjaju
void delete_bsn(char*); //brise \n na kraju stringa
int list_is_empty(NODE*);
void delete_last_node(NODE*);
int delete_event(NODE *, NODE**);//Brise dogadjaj koji se salje kao arg.
void change_info(NODE*); //Mijenja podatke o dogadjaju koji se salje kao arg.
int number_of_events(NODE*);//prebrojava broj dogadjaja
void sort_by_name(NODE** head, int count); //Sortira dogadjaje po imenu
void sort_by_location(NODE** head, int count); //Sortira dogadjaje po lokaciji
void sort_by_date(NODE** head, int count); //Sortira dogadjaje po datumu
void sort_by_category(NODE** head, int count);//Sortira po kategoriji
NODE* swap(NODE* ptr1, NODE* ptr2); //Mijenja mjesta 2 cvora liste
int choose_from_menu(int count); //Izbor iz menija. count-br. ponudjenih opcija u meniju
int date_input(int size, char* date); //Unos datuma (dan, mjesec ili godina)
NODE* choose_event(NODE* list, int n); //Vraca pokazivac na cvor odabranog dogadjaja.
void print_event_info(NODE* node); //Ispisuje informacije samo o jednom, odabranom, dogadjaju
int print_all_events(NODE* list); //Ispisuje samo imena svih dogadjaja i vraca broj dogadjaja
int print_all_events_info(NODE* list);

#endif // FUNKCIJE_H_INCLUDED
