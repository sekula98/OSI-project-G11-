#include "user_funkcije.h"

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

void print_event_info(NODE* node) {
	printf("\nNaziv: %s", node->info.name);
	int dd = atoi(node->info.day), mm = atoi(node->info.month), yy = atoi(node->info.year);
	printf("\nDatum: %02d/%02d/%4d", dd, mm, yy);
	printf("\nVrijeme: %s", node->info.time);
	printf("\nLokacija: %s", node->info.location);
	printf("\nKategorija: %s", node->info.category);
	printf("\nOpis: %s", node->info.description);
}

NODE* choose_event(NODE* list, int n) {
	int i;
	for (i = 0; i < n - 1; i++)
		list = list->next;
	return list;
}

void choose_category(FILE* fcategories, char* s) {
	char category[100];
	int i = 1, j;
	int tmp;
	printf("Postojece kategorije:\n");
	while (fgets(category, 101, fcategories)) {
		printf("%d. %s", i, category);
		i++;
	}
	printf("\n--------------------------------------------------------------------------------");
	printf("\nUpisite redni broj odabrane kategorije: ");
	tmp = choose_from_menu(i - 1);
	rewind(fcategories);
	for (j = 0; j < tmp; j++) {
		fgets(category, 101, fcategories);
	}
	delete_bsn(category);
	strcpy(s, category);
}

void print_comments(char* eventName)
{
	char comment[300];
	char datName[50]; FILE *f;
	strcpy(datName, eventName);
	strcat(datName, " komentari.txt");
	f = fopen(datName, "a");
	fclose(f);
	f = fopen(datName, "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	rewind(f);
	if (0 == size)
	{
		printf("\nNema komentara za izabrani dogadjaj!\n");
	}
	else
	{
		printf("\n================================================================================");
		printf("\n                             KOMENTARI                                          ");
		printf("\n================================================================================\n");
		while (fgets(comment, 51, f))
		{
			printf("- %s", comment);
		}
		printf("\n================================================================================\n");

	}

	fclose(f);
}

void add_comment(char* eventName)
{
	char newComment[300];
	char datName[100];
	FILE* fp;
	printf("\nUnesite komentar: ");
	fgets(newComment, 301, stdin); delete_bsn(newComment);
	strcpy(datName, eventName);
	strcat(datName, " komentari.txt");
	fp = fopen(datName, "a");
	fprintf(fp, "%s\n", newComment);
	fclose(fp);
}

void quiz()
{
    FILE* quizf;
    FILE* quizanswers;
    int sum = 0;
    char s[300];
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

int list_is_empty(NODE* list) {
	if (list) return 0;
	return 1;
}

int choose_from_menu(int count) {
	char s[20];
	int a = 0;
	int tmp;
	int i;

	printf("");
	fgets(s, 21, stdin);
	do {
		for (i = 1; i <= count; i++) {
			tmp = atoi(s);
			if (tmp == i) a++;
		}
		if (!a) {
			printf("\nNeispravan unos! Pokusajte ponovo: ");
			fgets(s, 21, stdin);
		}
	} while (!a);
	return tmp;
}

void print_hello()
{
    int x; double y;
   char text1[]=    "\n\n \t\t\t Dobro dosli u 'Above' ";
   char text2[]=    "\n\n \t\t\t By ";
   char text3[]=    "\n\n \t\t\t G11 ";
    printf("\n\n");
    for(x=0; text1[x]!=NULL; x++)
   {
     printf("%c",text1[x]);
      for(y=0; y<=8888888; y++)
      {
      }
   }
   printf("\n\n");
    for(x=0; text2[x]!=NULL; x++)
   {
     printf("%c",text2[x]);
      for(y=0; y<=8888888; y++)
      {
      }
   }
   printf("\n\n");
    for(x=0; text3[x]!=NULL; x++)
   {
     printf("%c",text3[x]);
      for(y=0; y<=8888888; y++)
      {
      }
   }
}
