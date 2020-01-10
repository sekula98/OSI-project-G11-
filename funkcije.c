#include "funkcije.h"

void read_user_info(char *id, char* pass)
{
	char tmp[50];
	FILE*F = fopen("podaci.txt", "r");
	if (F)
	{
		fgets(tmp, 51, F);
		delete_bsn(tmp);
		strcpy(id, tmp);
		fgets(tmp, 51, F);
		delete_bsn(tmp);
		strcpy(pass, tmp);
	}
	else
		printf("Ne moze se otvoriti datoteka");
	fclose(F);
}
char * enter_password(char * userName) //pisanje * umjesto sifre
{
	int i;
	char c;
	for (i = 0; i < 100; i++)
	{
		c = getch();
		if (c == 13)          // 13 je ascii value od enter
			break;

		if (isprint(c))
		{
			userName[i] = c;

			printf("%c", '*');
		}
		else if (c == 8 && i)  // 8 je ascii value od backspace
		{
			userName[--i] = '\0';
			i--;
			printf("%s", "\b \b");
		}
	}
	userName[i] = '\0';
	return userName;

}
void login()
{
	char userName[50], password[50], user[50], pass[50];
	int dozvola = 0, pom = 0;
	do {
		read_user_info(user, pass);
		if (pom == 0)
		{
			printf("Unesite ime: ");
			fgets(userName, 51, stdin);
			delete_bsn(userName);
		}
		printf("Unesite sifru: ");
		enter_password(password);
		if (strcmp(userName, user) == NULL)
		{
			if (strcmp(password, pass) == NULL)
			{
				dozvola = 1;
				printf("\n\n                            > Dobro dosli '%s'! <                            \n\n", userName);
			}
			else
			{
				printf(" Netacna sifra!\n");
				pom = 1;
			}
		}
		else
			printf("\nKorisnicko ime nije tacno!\n");
	} while (!dozvola);

}
void make_predef_cat()
{
	FILE *categoriesf;
	categoriesf = fopen("imena_kat.txt", "a");
	if (NULL != categoriesf)
	{
		fseek(categoriesf, 0, SEEK_END);		//provjera da li je prazna datoteka
		int size = ftell(categoriesf);

		if (0 == size)
		{
			fprintf(categoriesf, "izlozbe\n");
			fprintf(categoriesf, "koncerti\n");
			fprintf(categoriesf, "promocije\n");
		}
	}

	fclose(categoriesf);
}
void add_category()
{
	FILE* CatNameF;
	char nova_kategorija[100];

	printf("\nUnesite ime nove kategorije: ");
	fgets(nova_kategorija, 101, stdin); delete_bsn(nova_kategorija);
	CatNameF = fopen("imena_kat.txt", "a");  //upisuje imena kategorija u datoteku
	fprintf(CatNameF, "%s\n", nova_kategorija);

	fclose(CatNameF);
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
void delete_comment(char* eventName)
{
	int i, j, k;
	char tmp[300];
	char** comments = (char **)malloc(100 * sizeof(char *));
	char fileName[50];
	FILE *fp;
	i = 0;
	strcpy(fileName, eventName);
	strcat(fileName, " komentari.txt");
	fp = fopen(fileName, "a");
	fclose(fp);
	fp = fopen(fileName, "r");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		rewind(fp);
		if (size==0)
		{
			printf("\nNema komentara za izabrani dogadjaj!\n");
			fclose(fp);
		}
		else
		{
			while (fgets(tmp, 301, fp)) //dodaje komentare u niz
			{
				delete_bsn(tmp);
				comments[i] = (char *)calloc(strlen(tmp) + 1, sizeof(char));
				strcpy(comments[i++], tmp);
			}
			printf("\nKoji komentar zelite da izbrisete?");
			printf("\n--------------------------------------------------------------------------------");
			for (j = 0; j<i; j++)
			{
				printf("\n%d. %s", j + 1, comments[j]); //Ispisuje komentare
			}
			printf("\n--------------------------------------------------------------------------------");
			printf("\nOdaberite opciju: ");
			int m = choose_from_menu(j + 1);

			fclose(fp);

			fp = fopen(fileName, "w");
			//vraca sve sem odabranog komentara u datoteku
			for (k = 0; k<m - 1; k++)
				fprintf(fp, "%s\n", comments[k]);

			for (k = m; k < i; k++)
				fprintf(fp, "%s\n", comments[k]);

			fclose(fp);
		}
	}
	free(comments);
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

void print_categories()
{
	FILE* categoriesF;
	char category[50];
	categoriesF = fopen("imena_kat.txt", "r");
	if (categoriesF)
	{
		fseek(categoriesF, 0, SEEK_END);
		int size = ftell(categoriesF);
		rewind(categoriesF);
		if (0 == size)
		{
			printf("\nNema kategorija!");
		}
		else
		{
			printf("\n================================================================================");
			printf("\n                             KATEGORIJE                                         ");
			printf("\n================================================================================\n");
			while (fgets(category, 51, categoriesF))
			{
				printf("-  %s", category);
			}
			printf("\n================================================================================\n");
		}
	}
	fclose(categoriesF);
}
void delete_category()
{
	FILE* categoriesF;
	int i=0, j, k;
	char tmp[50];
	char** categories = (char **)malloc(100 * sizeof(char *));
	categoriesF = fopen("imena_kat.txt", "r");

	if (categoriesF)
	{
		fseek(categoriesF, 0, SEEK_END);
		int size = ftell(categoriesF);
		rewind(categoriesF);
		if (0 == size)
		{
			printf("\nNema kategorija!\n");
			fclose(categoriesF);
		}
		else
		{
			printf("\nKategorije: ");
			printf("\n--------------------------------------------------------------------------------");
			while (fgets(tmp, 51, categoriesF)) //dodaje kategoriju u niz
			{
				delete_bsn(tmp);
				categories[i] = (char *)calloc(strlen(tmp) + 1, sizeof(char));
				strcpy(categories[i++], tmp);
			}
			for (j = 0; j<i; j++)
			{
				printf("\n%d. %s", j + 1, categories[j]);
			}
			printf("\n--------------------------------------------------------------------------------");
			printf("\nOdaberite kategoriju: ");
			int m = choose_from_menu(j + 1);
			j = m - 1;

			fclose(categoriesF);
			//brise izabranu kategoriju
			categoriesF = fopen("imena_kat.txt", "w");
			for (k = 0; k <m - 1; k++)
				fprintf(categoriesF, "%s\n", categories[k]);

			for (k = m; k<i; k++)
					fprintf(categoriesF, "%s\n", categories[k]);

			fclose(categoriesF);
		}
	}
	free(categories);
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

EVENT event_info() {
	FILE* fcategories;
	EVENT event;
	char category[100];
	char fileName[50];
	FILE* f;
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
	do { printf("\nMjesec: "); i = date_input(12, event.month); } while (!i);
	do { printf("\nGodina: "); i = date_input(9999, event.year); } while (!i);
	printf("\nVrijeme odrzavanja: "); fgets(event.time, 21, stdin); delete_bsn(event.time);
	printf("\nLokacija odrzavanja: "); fgets(event.location, 101, stdin); delete_bsn(event.location);
	printf("\nOpis dogadjaja: "); fgets(event.description, 201, stdin); delete_bsn(event.description);
	printf("\nDa li zelite dodati komentar?  "); printf("1.Da 2.Ne"); printf("\nOdaberite opciju: ");
	int m = choose_from_menu(2);
	if (m == 1)
	{
		add_comment(event.name);
	}
	else if (m == 2)
	{
		strcpy(fileName, event.name);
		strcat(fileName, " komentari.txt");
		f = fopen(fileName, "w");
		fclose(f);
	}

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

void push_to_folder(NODE* node) {
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

void delete_bsn(char* s) {
	if ((strlen(s) > 0) && (s[strlen(s) - 1] == '\n'))
		s[strlen(s) - 1] = '\0';
}

void change_info(NODE* node) {
	int tmp;
	FILE*fcategories;
	char category[100];
	printf("\n\nSta zelite izmjeniti? ");
	printf("\n--------------------------------------------------------------------------------");
	printf("\n1.Naziv        2.Datum        3.Vrijeme");
	printf("\n4.Lokacija     5.Kategorija   6.Opis   ");
	printf("\n--------------------------------------------------------------------------------");
	printf("\nOdaberite opciju: ");
	tmp = choose_from_menu(6);
	if (tmp == 1) { printf("\nNaziv: "); fgets(node->info.name, 101, stdin); delete_bsn(node->info.name); }
	else if (tmp == 2) {
		printf("\nDatum odrzavanja: ");
		int i;
		do { printf("\nDan: "); i = date_input(31, node->info.day); } while (!i);
		do { printf("\nMjesec: "); i = date_input(12, node->info.month); } while (!i);
		do { printf("\nGodina: "); i = date_input(9999, node->info.year); } while (!i);
	}
	else if (tmp == 3) {
		printf("\nVrijeme: ");  fgets(node->info.time, 101, stdin); delete_bsn(node->info.time);
	}
	else if (tmp == 4) {
		printf("\nLokacija: ");  fgets(node->info.location, 101, stdin); delete_bsn(node->info.location);
	}
	else if (tmp == 5)
	{
		printf("\nU koju kategoriju zelite da premjestite dogadjaj?");
		printf("\n--------------------------------------------------------------------------------");
		if (fcategories = fopen("imena_kat.txt", "r"))
		{
			choose_category(fcategories, category);
			strcpy(node->info.category, category);
			fclose(fcategories);
		}

	}
	else if (tmp == 6) {
		printf("\nOpis: ");  fgets(node->info.description, 201, stdin); delete_bsn(node->info.description);
	}
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
		/* Predji na zadnji cvor u listi*/
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

			/* Odvaja zadnji od predzadnjeg cvora */
			preNode->next = NULL;
		}

		/* Izbrisi zadnji cvor */
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

				/* azuriraj  vezu nakon zamjene*/
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* prekini ako je iteracija zavrsena bez zamjene */
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

				/* azuriraj  vezu nakon zamjene*/
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* prekini ako je iteracija zavrsena bez zamjene */
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

				/* azuriraj  vezu nakon zamjene*/
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* prekini ako je iteracija zavrsena bez zamjene */
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

				/* azuriraj vezu nakon zamjene */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* prekini petlju ako se iteracija zavrsi bez zamjene */
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

int is_valid_number(char * string)
{
	int i;
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
	printf("\nNedozvoljen unos! Pokusajte ponovo: ");

	return 0;
}
