#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <string.h>
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

void citanje_podataka(char *,char*);
char * unos_kor_sifre(char * );
void login();
int choose_from_menu(int );
void kreiranje_def_kat();
void dodavanje_kategorije();
void prikaz_kategorija();
void brisanje_kategorije();
void dodavanje_komentara(char*);
void prikaz_komentara(char*);
void brisanje_komentara(char*);
void pull_from_folder(NODE**); //skida sadrzaj datoteke sa dogadjajima u listu
void push_to_folder(NODE*); //vraca listu sa dogadjajima u datoteku
void choose_category(FILE* fcategories, char*); //bira kategoriju dogadjaja
void add_event(NODE**, EVENT); //dodaje novi dogadjaj
EVENT event_info(); //unos informacija o dogadjaju
void delete_bsn(char*); //brise \n na kraju stringa
void quiz(); //Kviz
void comment_event(char*); //Prikaz postojecih i dodavanje novi komentara na dogadjaj. Argument je ime dogadjaja
int list_is_empty(NODE*);
void delete_last_node(NODE*);
int delete_event(NODE *, NODE** );//Brise dogadjaj koji se salje kao arg.
void change_info(NODE*); //Mijenja podatke o dogadjaju koji se salje kao arg.
int number_of_events(NODE*);//prebrojava broj dogadjaja
void sort_by_name(NODE** head, int count); //Sortira dogadjaje po imenu
void sort_by_location(NODE** head, int count); //Sortira dogadjaje po lokaciji
void sort_by_date(NODE** head, int count); //Sortira dogadjaje po datumu
void sort_by_category(NODE** head, int count);//Sortira po kategoriji
NODE* swap(NODE* ptr1, NODE* ptr2); //Mijenja mjesta 2 cvora liste
int choose_from_menu(int size); //Izbor iz menija. size-br. ponudjenih opcija u meniju
int date_input(int size, char* date); //Unos datuma (dan, mjesec ili godina)
NODE* choose_event(NODE* list, int n); //Vraca pokazivac na cvor odabranog dogadjaja.
void print_event_info(NODE* node); //Ispisuje informacije samo o jednom, odabranom, dogadjaju
int print_all_events(NODE* list); //Ispisuje samo imena svih dogadjaja i vraca broj dogadjaja
int print_all_events_info(NODE* list);

int main() {
    int i=0,x,y,trg=0,n,m,empty;
    int h,g;
    char trash[200];
    int dozvola=0;
    NODE* head = NULL;
    NODE*pom=NULL;
    pull_from_folder(&head);
    kreiranje_def_kat();
    login();
    fgets(trash,201,stdin);
    do
    {   printf("\nOpcije:");
        printf("\n--------------------------------------------------------------------------------");
        printf("\n1.Upravljanje kategorijama 2.Upravljanje dogadjajima 3.Kraj");
        printf("\n--------------------------------------------------------------------------------");
        printf("\nOdaberite opciju: ");
        y=choose_from_menu(3);
        printf("\n================================================================================\n\n");
        if (y==1)
        {
            do
            {   printf("\nOpcije:");
                printf("\n--------------------------------------------------------------------------------");
                printf("\n1.Prikazi postojece kategorije. 2.Dodaj novu kategoriju. 3.Izbrisi kategoriju\n4.Nazad");
                printf("\n--------------------------------------------------------------------------------");
                printf("\nOdaberite opciju: ");
                x=choose_from_menu(4);
                printf("\n================================================================================\n\n");
                if(x==2)
                {
                    dodavanje_kategorije();
                }

                if (x==1)
                {
                    prikaz_kategorija();
                }
                if(x==3)
                {
                    brisanje_kategorije();
                }
                if(x==4)
                    trg=1;
            }
            while(!trg);

        }
        else if(y==2)
        {
            trg=0;
            do
            {   printf("\nOpcije:");
                printf("\n--------------------------------------------------------------------------------");
                printf("\n1.Prikazi dogadjaje  2.Dodaj novi dogadjaj  3.Izbrisi dogadjaj\n4.Izmijeni dogadjaj  5.Komentari            6.Nazad");
                printf("\n--------------------------------------------------------------------------------");
                printf("\nOdaberite opciju: ");
                x=choose_from_menu(6);
                printf("\n================================================================================\n\n");
                if(x==1)
                {
                    if(list_is_empty(head))
                        printf("\nLista dogadjaja je prazna!\n");
                    else
                    {
                        printf("\nDa li zelite sortirati dogadjaje prije prikazivanja? 1.Da 2.Ne : ");
                        h=choose_from_menu(2);
                        if(h==1)
                        {
                            printf("\nPo kojem polju ih zelite sortirati?");
                            printf("\n--------------------------------------------------------------------------------");
                            printf("\n1.Datum  2.Lokacija  3.Ime\n4.Kategorija?");
                            printf("\n--------------------------------------------------------------------------------");
                            printf("\nOdaberite opciju: ");
                            g=choose_from_menu(4);
                            printf("\n================================================================================\n\n");
                            n=number_of_events(head);
                            if(g==1)
                            {
                                sort_by_date(&head,n);
                            }
                            else if(g==2)
                            {
                                sort_by_location(&head,n);
                            }
                            else if(g==3)
                            {
                                sort_by_name(&head,n);
                            }
                            else if(g==4)
                            {
                                sort_by_category(&head,n);
                            }
                        }
                        else if(h==2)
                        {
                            print_all_events_info(head);
                        }
                    }

                }
                if (x==2)
                {
                    add_event(&head, event_info());
                    push_to_folder(head);
                }
                if (x==3)
                {
                    if(list_is_empty(head))
                        printf("\n Lista dogadjaja je prazna!\n");
                    else
                    {
                        n=print_all_events(head);
                        printf("\n--------------------------------------------------------------------------------");
                        printf("\nIzaberite dogadjaj koji zelite da izbrisete: ");
                        m=choose_from_menu(n);
                        printf("\n================================================================================\n\n");
                        delete_event(choose_event(head,m),&head);
                    }

                }
                if (x==4)
                {
                    if(list_is_empty(head))
                        printf("\n Lista dogadjaja je prazna!\n");
                    else
                    {
                        n=print_all_events(head);
                        printf("\nIzaberite dogadjaj koji zelite da izmjenite: ");
                        printf("\n--------------------------------------------------------------------------------");
                        m=choose_from_menu(n);
                        printf("\n================================================================================\n\n");
                        pom=choose_event(head,m);
                        print_event_info(pom);
                        change_info(pom);
                    }
                }
                if (x==5)
                {
                    if(list_is_empty(head))
                        printf("\nLista dogadjaja je prazna!\n");
                    else
                    {
                        trg=0;
                        int trg1=0;
                        printf("\nZa koji dogadjaj zelite uredjivati komentar?");
                        printf("\n--------------------------------------------------------------------------------");
                        h=print_all_events(head);
                        printf("\n--------------------------------------------------------------------------------");
                        printf("\nOdaberite opciju: ");
                        pom=choose_event(head,choose_from_menu(h));
                        printf("\n================================================================================\n\n");
                        do
                        {
                            printf("\n1.Dodavanje komentara 2.Pregled komentara 3.Brisanje komentara\n 4.Nazad");
                            printf("\n--------------------------------------------------------------------------------");
                            printf("\nOdaberite opciju: ");
                            g=choose_from_menu(4);
                            printf("\n================================================================================\n\n");
                            if(g==1)
                            {
                                dodavanje_komentara(pom->info.name);
                            }
                            if(g==2)
                            {
                                prikaz_komentara(pom->info.name);
                            }
                            if(g==3)
                            {
                                brisanje_komentara(pom->info.name);
                            }
                            if(g==4)
                                trg1=1;
                        }
                        while(!trg1);
                    }
                }
                if (x==6)
                    trg=1;
            }
            while(!trg);
        }
        else if(y==3)
            printf("Kraj");

    }

    while(y==1||y==2);

}
void citanje_podataka(char *id,char* pass)
{
    int c=0;
    char pom[50];
    FILE*F=fopen("podaci.txt","r");
    if(F)
    {
        while(!feof(F))
        {
            fscanf(F,"%s",pom);
            if(!c)
            {
                strcpy(id,pom);
                c++;
            }
            else
                strcpy(pass,pom);
        }
    }
    else
        printf("Ne moze se otvoriti datoteka");
    fclose(F);
}
char * unos_kor_sifre(char * kor_sifra) //pisanje * umjesto sifre
{
    int i;
    char c;
    for(i = 0; i < 100; i++)
    {
        c = getch();
        if(c == 13)          // 13 je ascii value od enter
            break;

        if(isprint(c))
        {
            kor_sifra[i] = c;

            printf("%c", '*');
        }
        else if(c==8&& i)  // 8 je ascii value od backspace
        {
            kor_sifra[--i]='\0';
            i--;
            printf("%s", "\b \b");
        }
    }
    kor_sifra[i] = '\0';
    return kor_sifra;

}
void login()
{
    char kor_ime[50],kor_sifra[50],user[50],pass[50];
    int dozvola =0,pom=0;
    do {
        citanje_podataka(user,pass);
        if (pom==0)
        {
            printf("Unesi ime:\n");
            scanf("%s",kor_ime);
        }
        printf("Unesi sifru:\n");
        unos_kor_sifre(kor_sifra);

        if(!strcmp(kor_ime,user))
        {
            if(!strcmp(kor_sifra,pass))
            {
                dozvola=1;
                printf("\nDobro dosli %s!\n",kor_ime);
            }
            else
            {
                printf("Sifra nije tacna!\n");
                pom=1;
            }
        }
        else
            printf("\nKorisnicko ime nije tacno!\n");
    }
    while(!dozvola);

}
void kreiranje_def_kat()
{
//    f1=fopen("izlozbe.txt","a");
//    fclose(f1);
//    f2=fopen("koncerti.txt","a");
//    fclose(f2);
//    f3=fopen("promocije.txt","a");
//    fclose(f3);
 FILE *f4;
    f4=fopen("imena_kat.txt","a");
    if (NULL != f4)                 //provjera da li je prazna datoteka
    {
        fseek (f4, 0, SEEK_END);
        int size = ftell(f4);

        if (0 == size)
        {
            fprintf(f4,"izlozbe\n");
            fprintf(f4,"koncerti\n");
            fprintf(f4,"promocije\n");
        }
    }

    fclose(f4);
}
void dodavanje_kategorije()
{ FILE* imena_kat;
    char nova_kategorija[50];
    printf("\nUnesite ime nove kategorije: ");
    //getchar();
    fgets(nova_kategorija,51,stdin);
    imena_kat=fopen("imena_kat.txt","a");//upisuje imena kategorija u datoteku
    fprintf(imena_kat,"%s",nova_kategorija);//
    fclose(imena_kat);
}
void dodavanje_komentara(char *imee)
{
    char novi_komentar[200];
    char ime[50];FILE* f;
    printf("Unesite komentar\n");
    fgets(novi_komentar,201,stdin);
    //delete_bsn(novi_komentar);
    strcpy(ime,imee);
    strcat(ime," komentari.txt");
    f=fopen(ime,"a");
    fprintf(f,"%s",novi_komentar);
    fclose(f);
}
void brisanje_komentara(char *imee)
{
    int i,j,o,check=0;
    char niz_kat[50],**pom,brisi_fajl[50],trash[200];
    char ime[50];FILE *f;
    pom= (char **)malloc(100 * sizeof(char *));
    i=0;
 strcpy(ime,imee);
    strcat(ime," komentari.txt");
    f=fopen(ime,"r");
    if(f)
    {
        fseek (f, 0, SEEK_END);
        int size = ftell(f);
        rewind(f);
        if (0 == size)
        {
            printf("\nNema komentara za izabrani dogadjaj\n");
            check=1;
        }
        else
        {
            printf("\nIzaberite koji komentar zelite da izbrisete\n");
            while(fgets(niz_kat,51,f)) //dodaje kategoriju u niz
            {
                pom[i] = (char *)calloc(strlen(niz_kat) + 1, sizeof(char));
                strcpy(pom[i++], niz_kat);
            }
            for(j=0; j<i; j++)
            {
                printf(" %d. %s",j+1,pom[j]);
            }
            printf("\nOdaberite opciju: ");
            j=choose_from_menu(j+1);
            j=j-1;
        }
    }
    fclose(f);
    if(!check)
    {
        f=fopen(ime,"w");
        for (o = j ; o <i-1; o++) //brise izabranu kategoriju
        {
            pom[o]=pom[o+1];
        }
        for(o=0; o<i-1; o++)
        {
            fprintf(f,"%s",pom[o]);
            free(pom[o]);
        }
        fclose(f);

    }
    printf("");
       //fgets(trash,201,stdin);

}
void prikaz_komentara(char* imee)
{
    char ispis_kom[500];
    char ime[50];FILE *f;
   strcpy(ime,imee);
    strcat(ime," komentari.txt");
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

void prikaz_kategorija()
{
    FILE* imena_kat;
    char ispis_kat[50];
    imena_kat=fopen("imena_kat.txt","r");
    if(imena_kat)
    {
        fseek (imena_kat, 0, SEEK_END);
        int size = ftell(imena_kat);
        rewind(imena_kat);
        if (0 == size)
        {
            printf("Nema komentara za izabrani dogadjaj");
        }
        else
        {
    printf("\n================================================================================");
	printf("\n                             KATEGORIJE                                         ");
	printf("\n================================================================================\n");
        while(fgets(ispis_kat,51,imena_kat))
        {
            printf("-  %s",ispis_kat);
        }
        printf("\n================================================================================\n");
        }
    }
    fclose(imena_kat);
}
void brisanje_kategorije()
{
    FILE* imena_kat;
    int i,o,j;
    char niz_kat[50],**pom,brisi_fajl[50];
    pom= (char **)malloc(100 * sizeof(char *));
    i=0;
    imena_kat=fopen("imena_kat.txt","r");
    if(imena_kat)
    {
        printf("Izaberite koju kategoriju zelite da izbrisete\n");
        while(fgets(niz_kat,51,imena_kat)) //dodaje kategoriju u niz
        {
            pom[i] = (char *)calloc(strlen(niz_kat) + 1, sizeof(char));
            strcpy(pom[i++], niz_kat);
        }
        for(j=0; j<i; j++)
        {
            printf(" %d. %s",j+1,pom[j]);
        }
        printf("Odaberite opciju: ");
       j=choose_from_menu(j+1);
        j=j-1;
    }
    fclose(imena_kat);
    imena_kat=fopen("imena_kat.txt","w");
    for (o = j ; o <i-1; o++) //brise izabranu kategoriju
    {
        pom[o]=pom[o+1];
    }
    for(o=0; o<i-1; o++)
    {
        fprintf(imena_kat,"%s",pom[o]);
        free(pom[o]);
    }
    fclose(imena_kat);

}

void choose_category(FILE* fcategories, char* s) {
	char category[100];
	int i = 1,j;
	int tmp;
	printf("Postojece kategorije:\n");
	while (fgets(category, 101, fcategories)) {
		printf("%d. %s", i, category);
		i++;
	}
	printf("\n\nUpisite redni broj odabrane kategorije: ");
	tmp=choose_from_menu(i-1);
	rewind(fcategories);
	for (j = 0; j < tmp; j++) {
		fgets(category, 101, fcategories);
	}
	delete_bsn(category);
	strcpy(s, category);
}

EVENT event_info() {
	FILE* fcategories;
	EVENT event;
	char pom[51];
	//char trash[100];
	char category[100];
    char ime[50];FILE* f;
	if (fcategories = fopen("imena_kat.txt", "r")) {
		choose_category(fcategories, category);
		strcpy(event.category, category);
		fclose(fcategories);
	}
	else printf("Greska pri otvaranju datoteke sa kategorijama!");
	printf("");
	//fgets(trash, 101, stdin);
	printf("\nNaziv dogadjaja: ");
	fgets(event.name, 101, stdin);
	printf("");
	delete_bsn(event.name);
	printf("\nDatum odrzavanja");
	int i;
	do { printf("\nDan: "); i = date_input(31, event.day); } while (!i);
	do { printf("\nMjesec: "); i=date_input(12, event.month); } while (!i);
	do { printf("\nGodina: "); i = date_input(9999, event.year); } while (!i);
	printf("\nVrijeme odrzavanja: "); fgets(event.time, 21, stdin); delete_bsn(event.time);
	printf("\nLokacija odrzavanja: "); fgets(event.location, 101, stdin); delete_bsn(event.location);
	printf("\nOpis dogadjaja: "); fgets(event.description, 201, stdin); delete_bsn(event.description);
	printf("Da li zelite dodati komentar?\n"); printf("\n1.Da 2.Ne\n");
    do {
        fgets(pom,51,stdin);
        if(pom[0]=='1')
        {
            dodavanje_komentara(event.name);
            break;
        }
        else if (pom[0]=='2')
        {
            strcpy(ime,event.name);
            strcat(ime," komentari.txt");
            f=fopen(ime,"w");
            fclose(f);
        }
            break;
        printf("Pogresan unos\n");
    }
    while(pom[0]!='1' || pom[0]!='2');
    return event;
}

void pull_from_folder(NODE** head) {
	FILE* eventsf;
	if (eventsf = fopen("Dogadjaji.txt", "a+")) {
		fseek(eventsf, 0, SEEK_END);
		int size = ftell(eventsf);
		rewind(eventsf);
		if (size) { //provjerava da li je datoteka sa dogadjajima prazna
			EVENT tmp;
			while (fgets(tmp.name, 101, eventsf)) {
				delete_bsn(tmp.name);
				fgets(tmp.category, 101, eventsf); delete_bsn(tmp.category);
				fgets(tmp.day, 4, eventsf); delete_bsn(tmp.day);
				fgets(tmp.month, 4, eventsf); delete_bsn(tmp.month);
				fgets(tmp.year, 6, eventsf); delete_bsn(tmp.year);
				fgets(tmp.time, 21, eventsf); delete_bsn(tmp.time);
				fgets(tmp.location, 101, eventsf); delete_bsn(tmp.location);
				fgets(tmp.description, 201, eventsf); delete_bsn(tmp.description);
				add_event(head, tmp);
			}
			fclose(eventsf);
		}
	}
	else printf("Greska pri otvaranju datoteke sa dogadjajima za skidanje podataka o dogadjajima!");
}

void push_to_folder(NODE*node) {
	FILE* eventsf;
	if (eventsf = fopen("Dogadjaji.txt", "w")) {
		while (node) {
			fprintf(eventsf, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", node->info.name, node->info.category, node->info.day, node->info.month, node->info.year, node->info.time, node->info.location, node->info.description);
			node = node->next;
		}
		fclose(eventsf);
	}
	else printf("\nGreska pri otvaranju datoteke sa dogadjajima za azuriranje podataka!");
}

void add_event(NODE **head, EVENT info) {
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

int print_all_events(NODE* list) {
	int n = 0;
		while (list) {
			printf("\n%d. %s", ++n, list->info.name);
			list = list->next;
	}
		return n;
}

int print_all_events_info(NODE* list) {
	int n = 0;
	printf("\n================================================================================");
	printf("\n                              LISTA  DOGADJAJA                                  ");
	printf("\n================================================================================");
	while (list) {
		printf("\nIme: %s", list->info.name);
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
int number_of_events(NODE*list)
{
   int n = 0;
   while (list) {
		list = list->next;
		n++;
	}
	return n;
}

void print_event_info(NODE* node) {
	printf("\nIme: %s", node->info.name);
	int dd = atoi(node->info.day), mm = atoi(node->info.month), yy = atoi(node->info.year);
	printf("\nDatum: %02d/%02d/%4d", dd, mm, yy);
	printf("\nVrijeme: %s", node->info.time);
	printf("\nLokacija: %s", node->info.location);
	printf("\nKategorija: %s", node->info.category);
	printf("\nOpis: %s", node->info.description);
}

NODE* choose_event(NODE* list, int n) {
    int i;
	for ( i = 0; i < n-1; i++)
		list = list->next;
	return list;
}

void delete_bsn(char* s) {
	if ((strlen(s) > 0) && (s[strlen(s) - 1] == '\n'))
		s[strlen(s) - 1] = '\0';
}

void quiz() {
	FILE* quizf;
	FILE* quizanswers;
	int sum = 0;
	char s[100];
	char a[10];
	char af[2];
	int i;
	if ((quizf = fopen("quiz data.txt", "r")) && (quizanswers = fopen("quiz answers.txt", "r"))) {
		for (i = 0; i < 3; i++) {
			printf("\n");
			fgets(s, 101, quizf); printf("%s", s);
			fgets(s, 101, quizf); printf("%s", s);
			fscanf(quizanswers,"%s", af);
			printf("\nUnesite slovo ispred tacnog odgovora: "); scanf("%s", a);
			if (!strcmp(af, a)) {
				sum++;
				printf("\nTacan odgovor!");
			}
			else {
				printf("\nNetacan odgovor!");
				printf("\nTacan odgovor je pod %s", af);

			}
		}
		printf("\nBroj tacnih odgovora: %d", sum);
	}
	else printf("Greska pri pokretanju kviza!");
}

void comment_event(char* name) {
	FILE* commentsf;
	char tmp[120];
	strcpy(tmp, name);
	strcat(tmp, " komentari.txt");
	if (commentsf = fopen(tmp, "a+")) {
		printf("\nDosadasnji komentari:\n\n");
		while (fgets(tmp, 121, commentsf))
			printf("%s", tmp);
		printf("\nUnesite svoj komentar:\n");// napraviti opciju Da li zelite da unesete svoj komentar.
		fgets(tmp, 121, stdin);
		fprintf(commentsf, "%s\n", tmp);
	}
	else printf("Greska pri otvaranju datoteke sa komentarima!");

}

void change_info(NODE* node) {
	int tmp;
	FILE*fcategories;
	char category[100];
	printf("\nSta zelite izmjeniti? ");
	printf("\n1.Naziv        2.Datum        3.Vrijeme");
	printf("\n4.Lokacija     5.Kategorija   6.Opis   ");

    tmp=choose_from_menu(6);
	if (tmp == 1) { printf("\nIme: "); fgets(node->info.name,100,stdin); }
	else if (tmp == 2) {
		printf("\nDatum odrzavanja: ");
		int i;
		do { printf("\nDan: "); i = date_input(31, node->info.day); } while (!i);
		do { printf("\nMjesec: "); i = date_input(12, node->info.month); } while (!i);
		do { printf("\nGodina: "); i = date_input(9999, node->info.year); } while (!i);
	}
	else if (tmp == 3) {
		printf("\nVrijeme:");  fgets(node->info.time,100,stdin);
	}
	else if (tmp == 4) {
		printf("\nLokacija:");  fgets(node->info.location,100,stdin);
	}
    else if (tmp == 5)
    {
        printf("\nDogadjaj se trenutno nalazi u kategoriji: %s\n",node->info.category);
        printf("Izaberite u koju kategoriju zelite da premjestite dogadjaj\n");
        if (fcategories = fopen("imena_kat.txt", "r"))
        {
            choose_category(fcategories, category);
            strcpy(node->info.category, category);
            fclose(fcategories);
        }

	}
	else if (tmp == 6) {
		printf("\nOpis:");  fgets(node->info.description,100,stdin);
	}
	else printf("Pogresan unos!"); //Onemoguciti pogresan unos!
}
int list_is_empty(NODE* list) {
	if (list) return 0;
	return 1;
}

void delete_last_node(NODE* list)
{
	NODE *toDelLast, *preNode;
	if (list == NULL)
	{
		printf("\nLista sa dogadjajima je prazna.");
	}
	else
	{
		toDelLast = list;
		preNode = list;
		/* Traverse to the last node of the list*/
		while (toDelLast->next != NULL)
		{
			preNode = toDelLast;
			toDelLast = toDelLast->next;
		}
		if (toDelLast == list)
		{
			list = NULL;
		}
		else
		{

			/* Disconnects the link of second last node with last node */
			preNode->next = NULL;
		}

		/* Delete the last node */
		free(toDelLast);
	}
}


int delete_event(NODE *node, NODE** list)
{
	NODE* p = *list;
	if (p->next == NULL) {
		*list = NULL;
		free(p);
		return 1;
	}
	NODE *q = node->next;
	if (q)
	{
		node->next = q->next;
		node->info = q->info;
		free(q);
	}
	else delete_last_node(*list);

	return 0;
}

void sort_by_name(NODE** head, int count)
{
	NODE** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			NODE* p1 = *h;
			NODE* p2 = p1->next;

			if (strcmp(p1->info.name, p2->info.name) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
}

void sort_by_date(NODE** head, int count)
{
	NODE** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			NODE* p1 = *h;
			NODE* p2 = p1->next;
			int dd1 = atoi(p1->info.day);
			int mm1 = atoi(p1->info.month);
			int yy1 = atoi(p1->info.year);
			int dd2 = atoi(p2->info.day);
			int mm2 = atoi(p2->info.month);
			int yy2 = atoi(p2->info.year);

			int sum1 = dd1 + (mm1 * 31) + (yy1 * 366);
			int sum2 = dd2 + (mm2 * 31) + (yy2 * 366);

			if (sum1 > sum2) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
}

void sort_by_location(NODE** head, int count)
{
	NODE** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			NODE* p1 = *h;
			NODE* p2 = p1->next;

			if (strcmp(p1->info.location, p2->info.location) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
}
void sort_by_category(NODE** head, int count)
{
	NODE** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			NODE* p1 = *h;
			NODE* p2 = p1->next;

			if (strcmp(p1->info.category, p2->info.category) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
}

NODE* swap(NODE* ptr1, NODE* ptr2)
{
	NODE* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

int choose_from_menu(int size) {
    char s[20];
    int a=0;
    int tmp;
    int i;

   printf("");
    fgets(s, 21, stdin);
    do {
        for (i = 1; i <= size; i++) {
            tmp = atoi(s);
            if (tmp == i) a++;
        }
            if (!a) {
                printf("\nNeispravan unos! Pokusajte ponovo: ");
                fgets(s, 21, stdin);
            }
        }while (!a);
        return tmp;
}

int is_valid_number(char * string)
{ int i;
	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] < 48 || string[i] > 57)
			return 0;
	}

	return 1;
}

int date_input(int size, char* date) {
	int num;
	char str[20];
	fgets(str, 21, stdin); delete_bsn(str);

	if (is_valid_number(str)) {
		num = atoi(str);
		if (num > 0 && num <= size) {
			strcpy(date, str);
			return 1;
		}
	}
	printf("  Nedozvoljen unos! Pokusajte ponovo.");
	return 0;
}
