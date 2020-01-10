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

int print_all_events_info(NODE* list);
void print_today_events(NODE* list);
void print_future_events(NODE* list);
void print_past_events(NODE* list);
void print_event_from_category(NODE* list);
void print_event_info(NODE*);
void choose_category(FILE* fcategories, char*);
int choose_from_menu(int count);
void quiz();
void delete_bsn(char* s);
void pull_from_folder(NODE** head); //skida sadrzaj datoteke sa dogadjajima u listu
void add_event(NODE** head, EVENT event);
int list_is_empty(NODE* list);
int print_all_events(NODE* list);
NODE* choose_event(NODE* list, int n);
void dodavanje_komentara(char*);
void prikaz_komentara(char*);

int main()

{
    NODE* head = NULL;
    NODE* pom = NULL;
    pull_from_folder(&head);
    int trg=0,x,y;
    char trash[100];
    do
    {
        printf("\nOpcije:");
        printf("\n--------------------------------------------------------------------------------");
        printf("\n1.Pregled dogadjaja. 2.Komentarisanje dogadjaja. 3.Igranje kviza o gradu\n4.Kraj");
        printf("\n--------------------------------------------------------------------------------");
        printf("\nOdaberite opciju: ");
        y=choose_from_menu(4);
        printf("\n================================================================================\n\n");
        if(y==1)
        {
            int trg1=0;
            do
            {
                printf("\nOpcije:");
                printf("\n--------------------------------------------------------------------------------");
                printf("\n1.Pregled svih dogadjaja                  2.Pregled danasnjih dogadjaja\n3.Pregled svih buducih dogadjaja          4.Pregled dogadjaja koji su prosli\n5.Pregled dogadjaja odredjenje kategorije 6.Nazad");
                printf("\n--------------------------------------------------------------------------------");
                printf("\nOdaberite opciju: ");
                x=choose_from_menu(6);
                if(x==1)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.");
                        getchar();
                    }
                    else
                    {
                        print_all_events_info(head);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==2)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.");
                        getchar();
                    }
                    else
                    {
                        print_today_events(head);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                }

                if (x==5)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_event_from_category(head);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==3)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_future_events(head);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==4)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_past_events(head);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==6)
                    trg1=1;
            }
            while(!trg1);

        }
        if(y==2)
        {
            if(list_is_empty(head))
            {
                printf("\nLista dogadjaja je prazna!\n");
                printf("\n\nPritisnite Enter.");
                fgets(trash, 101, stdin);
            }
            else
            {

                int h,g;
                printf("\nIzdaberite dogadjaj");
                printf("\n--------------------------------------------------------------------------------");
                h=print_all_events(head);
                printf("\n--------------------------------------------------------------------------------");
                printf("\nOdaberite opciju: ");
                pom=choose_event(head,choose_from_menu(h));
                printf("\n================================================================================\n\n");
                do
                {
                    printf("\n1.Dodavanje komentara 2.Pregled komentara 3.Nazad");
                    printf("\n--------------------------------------------------------------------------------");
                    printf("\nOdaberite opciju: ");
                    g=choose_from_menu(3);
                    printf("\n================================================================================\n\n");
                    if(g==1)
                    {
                        dodavanje_komentara(pom->info.name);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                    if(g==2)
                    {
                        prikaz_komentara(pom->info.name);
                        printf("\n\nPritisnite Enter.");
                        fgets(trash, 101, stdin);
                    }
                    if(g==3)
                        trg=1;
                }
                while(!trg);
            }
        }
        trg=0;

        if(y==3)
        {
            quiz();
            printf("\n1.Pokusaj ponovo 2.Kraj");
            int l=choose_from_menu(2);
            if(l==1)
                quiz();
            if(l==2)
            {
                printf("\n\nPritisnite Enter.");
                fgets(trash, 101, stdin);
            }
        }
        if(y==4)
        {
            trg=1;
            printf("KRAJ!");
        }
    }
    while(!trg);
}

void print_today_events(NODE* list)
{
    if (list)
    {
        int tmp=0;
        SYSTEMTIME t;
        GetLocalTime(&t);
        int pivot = t.wDay + (t.wMonth * 31) + (t.wYear * 366);
        printf("\n================================================================================");
        printf("\n                              LISTA  DANASNJIH  DOGADJAJA                                ");
        printf("\n================================================================================");
        while (list)
        {
            int dd = atoi(list->info.day);
            int mm = atoi(list->info.month);
            int yy = atoi(list->info.year);
            int sum = dd + (mm * 31) + (yy * 366);
            if (pivot == sum)
            {
                print_event_info(list);
                printf("\n--------------------------------------------------------------------------------");
                tmp++;
            }
            list = list->next;
        }
        if(tmp==0) printf("\nNema danasnjih dogadjaja!");
        printf("\n================================================================================\n");
    }
    else printf("\nLista sa dogadjajima je prazna!");
}

void print_future_events(NODE* list)
{
    if (list)
    {
        int tmp=0;
        SYSTEMTIME t;
        GetLocalTime(&t);
        int pivot = t.wDay + (t.wMonth * 31) + (t.wYear * 366);
        printf("\n================================================================================");
        printf("\n                           LISTA  BUDUCIH  DOGADJAJA                            ");
        printf("\n================================================================================");
        while (list)
        {
            int dd = atoi(list->info.day);
            int mm = atoi(list->info.month);
            int yy = atoi(list->info.year);
            int sum = dd + (mm * 31) + (yy * 366);
            if (pivot < sum)
            {
                print_event_info(list);
                printf("\n--------------------------------------------------------------------------------");
                tmp++;
            }
            list = list->next;
        }
        if(tmp==0) printf("\nNema buducih dogadjaja!");
        printf("\n================================================================================\n");
    }
    else printf("\nLista sa dogadjajima je prazna!");
}



void print_past_events(NODE* list)
{
    if (list)
    {
        int tmp=0;
        SYSTEMTIME t;
        GetLocalTime(&t);
        int pivot = t.wDay + (t.wMonth * 31) + (t.wYear * 366);
        printf("\n================================================================================");
        printf("\n                    LISTA  DOGADJAJA  KOJI  SU  PROSLI                          ");
        printf("\n================================================================================");
        while (list)
        {
            int dd = atoi(list->info.day);
            int mm = atoi(list->info.month);
            int yy = atoi(list->info.year);
            int sum = dd + (mm * 31) + (yy * 366);
            if (pivot > sum)
            {
                print_event_info(list);
                printf("\n--------------------------------------------------------------------------------");
                tmp++;
            }
            list = list->next;
        }
        if(tmp==0) printf("\nNema proslih dogadjaja!");
        printf("\n================================================================================\n");
    }
    else printf("\nLista sa dogadjajima je prazna!");
}

void print_event_from_category(NODE* list)
{
    int tmp=0;
    FILE* fcategories;
    char category[100];
    if (fcategories = fopen("imena_kat.txt", "a+"))
    {
        fseek(fcategories, 0, SEEK_END);
        int size = ftell(fcategories);
        rewind(fcategories);
        if (size)
        {
            choose_category(fcategories, category);
            fclose(fcategories);
            printf("\n================================================================================");
            printf("\n                   LISTA  DOGADJAJA  IZ  IZABRANE  KATEGORIJE                   ");
            printf("\n================================================================================");
            while (list)
            {
                if (strcmp(category, list->info.category) == 0)
                {
                    print_event_info(list);
                    printf("\n--------------------------------------------------------------------------------");
                    tmp++;
                }
                list = list->next;
            }
            if(tmp==0)printf("\nNema dogadjaja iz izabrane kategorije!");
            printf("\n================================================================================\n");
        }
        else printf("\nNema kategorija!");
    }
    else printf("Greska pri otvaranju datoteke sa kategorijama!");
}

void choose_category(FILE* fcategories, char* s)
{
    char category[100];
    int i = 1,j;
    int tmp;
    printf("Postojece kategorije:\n");
    while (fgets(category, 101, fcategories))
    {
        printf("%d. %s", i, category);
        i++;
    }
    printf("\n\nUpisite redni broj odabrane kategorije: ");
    tmp=choose_from_menu(i-1);
    rewind(fcategories);
    for (j = 0; j < tmp; j++)
    {
        fgets(category, 101, fcategories);
    }
    delete_bsn(category);
    strcpy(s, category);
}

int choose_from_menu(int size)
{
    char s[20];
    int a=0;
    int tmp;
    int i;

    printf("");
    fgets(s, 21, stdin);
    do
    {
        for (i = 1; i <= size; i++)
        {
            tmp = atoi(s);
            if (tmp == i) a++;
        }
        if (!a)
        {
            printf("\nNeispravan unos! Pokusajte ponovo: ");
            fgets(s, 21, stdin);
        }
    }
    while (!a);
    return tmp;
}
void quiz()
{
    FILE* quizf;
    FILE* quizanswers;
    int sum = 0;
    char s[300];
    char a[100];
    char af[2];
    int i;
    if ((quizf = fopen("quiz_data.txt", "r")) && (quizanswers = fopen("quiz_answers.txt", "r")))
    {
        printf("\n================================================================================");
        printf("\n                                      KVIZ                                        ");
        printf("\n================================================================================\n");
        for (i = 0; i < 10; i++)
        {
            printf("\n");
            fgets(s, 301, quizf);
            printf("%s", s);
            fgets(s, 301, quizf);
            printf("%s", s);
            fscanf(quizanswers,"%s", af);
            int tmp1=atoi(af);
            printf("\nUnesite odgovor: ");
            int tmp2=choose_from_menu(3);
            if (tmp1==tmp2)
            {
                sum++;
                printf("\nTacan odgovor!");
            }
            else
            {
                printf("\nNetacan odgovor! Tacan odgovor je pod %s", af);
            }
            printf("\n--------------------------------------------------------------------------------");
        }
        printf("\nKRAJ!   Broj tacnih odgovora: %d", sum);
        printf("\n================================================================================\n\n");
    }
    else printf("Greska pri pokretanju kviza!");
}
void delete_bsn(char* s)
{
    if ((strlen(s) > 0) && (s[strlen(s) - 1] == '\n'))
        s[strlen(s) - 1] = '\0';
}
void pull_from_folder(NODE** head)
{
    FILE* eventsf;
    if (eventsf = fopen("Dogadjaji.txt", "a+"))
    {
        fseek(eventsf, 0, SEEK_END);
        int size = ftell(eventsf);
        rewind(eventsf);
        if (size)   //provjerava da li je datoteka sa dogadjajima prazna
        {
            EVENT tmp;
            while (fgets(tmp.name, 101, eventsf))
            {
                delete_bsn(tmp.name);
                fgets(tmp.category, 101, eventsf);
                delete_bsn(tmp.category);
                fgets(tmp.day, 4, eventsf);
                delete_bsn(tmp.day);
                fgets(tmp.month, 4, eventsf);
                delete_bsn(tmp.month);
                fgets(tmp.year, 6, eventsf);
                delete_bsn(tmp.year);
                fgets(tmp.time, 21, eventsf);
                delete_bsn(tmp.time);
                fgets(tmp.location, 101, eventsf);
                delete_bsn(tmp.location);
                fgets(tmp.description, 201, eventsf);
                delete_bsn(tmp.description);
                add_event(head, tmp);
            }
            fclose(eventsf);
        }
    }
    else printf("Greska pri otvaranju datoteke sa dogadjajima za skidanje podataka o dogadjajima!");
}
void add_event(NODE **head, EVENT info)
{
    NODE *p, *newnode = (NODE *)malloc(sizeof(NODE));
    newnode->info = info;
    newnode->next = 0;
    if (*head == 0) *head = newnode;
    else
    {
        for (p = *head; p->next; p = p->next);
        p->next = newnode;
    }
}
int list_is_empty(NODE* list)
{
    if (list) return 0;
    return 1;
}

int print_all_events(NODE* list)
{
    int n = 0;
    while (list)
    {
        printf("\n%d. %s", ++n, list->info.name);
        list = list->next;
    }
    return n;
}
NODE* choose_event(NODE* list, int n)
{
    int i;
    for ( i = 0; i < n-1; i++)
        list = list->next;
    return list;
}
void dodavanje_komentara(char *imee)
{
    char novi_komentar[200];
    char ime[50];
    FILE* f;
    printf("Unesite komentar\n");
    fgets(novi_komentar,201,stdin);
    //delete_bsn(novi_komentar);
    strcpy(ime,imee);
    strcat(ime," komentari.txt");
    f=fopen(ime,"a");
    fprintf(f,"%s",novi_komentar);
    fclose(f);
}
void prikaz_komentara(char* imee)
{
    char ispis_kom[500];
    char ime[50];
    FILE *f;
    strcpy(ime,imee);
    strcat(ime," komentari.txt");
    f=fopen(ime,"a");
    fclose(f);
    f=fopen(ime,"r");
    if(f)
    {
        fseek (f, 0, SEEK_END);
        int size = ftell(f);
        rewind(f);
        if (0 == size)
        {
            printf("Nema komentara za izabrani dogadjaj");
        }
        else
        {
            printf("\n================================================================================");
            printf("\n                             KOMENTARI                                          ");
            printf("\n================================================================================\n");
            while(fgets(ispis_kom,51,f))
            {
                printf("-  %s",ispis_kom);
            }
            printf("\n================================================================================\n");
        }
    }

    fclose(f);
}
void print_event_info(NODE* node)
{
    printf("\nIme: %s", node->info.name);
    int dd = atoi(node->info.day), mm = atoi(node->info.month), yy = atoi(node->info.year);
    printf("\nDatum: %02d/%02d/%4d", dd, mm, yy);
    printf("\nVrijeme: %s", node->info.time);
    printf("\nLokacija: %s", node->info.location);
    printf("\nKategorija: %s", node->info.category);
    printf("\nOpis: %s", node->info.description);
}

int print_all_events_info(NODE* list) {
	int n = 0;
	printf("\n================================================================================");
	printf("\n                              LISTA  DOGADJAJA                                  ");
	printf("\n================================================================================");
	while (list) {
		printf("\nNaziv: %s", list->info.name);
		int dd = atoi(list->info.day), mm = atoi(list->info.month), yy = atoi(list->info.year);
		printf("\nDatum: %02d/%02d/%4d", dd, mm, yy);
		printf("\nVrijeme: %s", list->info.time);
		printf("\nLokacija: %s", list->info.location);
		printf("\nKategorija: %s", list->info.category);
		printf("\nOpis: %s", list->info.description);
		printf("\n--------------------------------------------------------------------------------");
		list = list->next;
		n++;
	}
	printf("\n================================================================================\n");
	return n;
}




