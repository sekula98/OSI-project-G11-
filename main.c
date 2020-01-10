#include "funkcije.h"
#include "funkcije.c"
wew
int main() {
	int i = 0, x, y, trg = 0, n, m, empty, h, g;
	char trash[200];
	int dozvola = 0;
	NODE* head = NULL;
	NODE*pom = NULL;

	pull_from_folder(&head);
	make_predef_cat();
	login();

	do
	{
		printf("\nOpcije:");
		printf("\n--------------------------------------------------------------------------------");
		printf("\n1.Upravljanje kategorijama 2.Upravljanje dogadjajima 3.Kraj");
		printf("\n--------------------------------------------------------------------------------");
		printf("\nOdaberite opciju: ");
		y = choose_from_menu(3);
		printf("\n================================================================================\n\n");
		if (y == 1)
		{
			trg = 0;
			do
			{
				printf("\nOpcije:");
				printf("\n--------------------------------------------------------------------------------");
				printf("\n1.Prikazi postojece kategorije. 2.Dodaj novu kategoriju. 3.Izbrisi kategoriju\n4.Nazad");
				printf("\n--------------------------------------------------------------------------------");
				printf("\nOdaberite opciju: ");
				x = choose_from_menu(4);
				printf("\n================================================================================\n\n");
				if (x == 2)
				{
					add_category();
				}

				else if (x == 1)
				{
					print_categories();
					printf("\nPritisnite Enter.\n");
                    fgets(trash, 201, stdin);
				}
				else if (x == 3)
				{
					delete_category();
				}
				else if (x == 4)
					trg = 1;
			} while (!trg);

		}
		else if (y == 2)
		{
			trg = 0;
			do
			{
				printf("\nOpcije:");
				printf("\n--------------------------------------------------------------------------------");
				printf("\n1.Prikazi dogadjaje  2.Dodaj novi dogadjaj  3.Izbrisi dogadjaj");
				printf("\n4.Izmijeni dogadjaj  5.Komentari            6.Nazad");
				printf("\n--------------------------------------------------------------------------------");
				printf("\nOdaberite opciju: ");
				x = choose_from_menu(6);
				printf("\n================================================================================\n\n");
				if (x == 1)
				{
					if (list_is_empty(head))
						printf("\nLista dogadjaja je prazna!\n");
					else
					{
						printf("\nDa li zelite sortirati dogadjaje prije prikazivanja? 1.Da 2.Ne : ");
						h = choose_from_menu(2);
						if (h == 1)
						{
							int k = 0;
							printf("\nPo kojem polju ih zelite sortirati?");
							printf("\n--------------------------------------------------------------------------------");
							printf("\n1.Datum  2.Lokacija  3.Ime\n4.Kategorija?");
							printf("\n--------------------------------------------------------------------------------");
							printf("\nOdaberite opciju: ");
							g = choose_from_menu(4);
							printf("\n================================================================================\n\n");
							n = number_of_events(head);
							if (g == 1)
							{
								sort_by_date(&head, n);
								k = 1;
							}
							else if (g == 2)
							{
								sort_by_location(&head, n);
								k = 1;
							}
							else if (g == 3)
							{
								sort_by_name(&head, n);
								k = 1;
							}
							else if (g == 4)
							{
								sort_by_category(&head, n);
								k = 1;
							}
							if (k)
								print_all_events_info(head);
								printf("\nPritisnite Enter.\n");
								fgets(trash, 201, stdin);

						}
						else if (h == 2)
						{
							print_all_events_info(head);
							printf("\nPritisnite Enter.\n");
                            fgets(trash, 201, stdin);
						}
					}

				}
				if (x == 2)
				{
					add_event(&head, event_info());
				}
				else if (x == 3)
				{
					if (list_is_empty(head))
						printf("\n Lista dogadjaja je prazna!\n");
					else
					{
						n = print_all_events(head);
						printf("\n--------------------------------------------------------------------------------");
						printf("\nIzaberite dogadjaj koji zelite da izbrisete: ");
						m = choose_from_menu(n);
						printf("\n================================================================================\n\n");
						delete_event(choose_event(head, m), &head);
					}

				}
				else if (x == 4)
				{
					if (list_is_empty(head))
						printf("\n Lista dogadjaja je prazna!\n");
					else
					{
						printf("\nLista dogadjaja:");
						printf("\n--------------------------------------------------------------------------------");
						n = print_all_events(head);
						printf("\n--------------------------------------------------------------------------------");
						printf("\nIzaberite dogadjaj koji zelite da izmjenite: ");
						m = choose_from_menu(n);
						printf("\n--------------------------------------------------------------------------------");
						printf("\n================================================================================\n\n");
						pom = choose_event(head, m);
						print_event_info(pom);
						int tmp = 1;
						do {
							change_info(pom);
							printf("\n1. Nova izmjena  2.Nazad");
							printf("\n--------------------------------------------------------------------------------");
							printf("\nOdaberite opciju: ");
							if (choose_from_menu(2) == 2) tmp = 0;
						} while (tmp);
					}
				}
				else if (x == 5)
				{
					if (list_is_empty(head))
						printf("\nLista dogadjaja je prazna!\n");
					else
					{
						trg = 0;
						int trg1 = 0;
						printf("\nZa koji dogadjaj zelite uredjivati komentar?");
						printf("\n--------------------------------------------------------------------------------");
						h = print_all_events(head);
						printf("\n--------------------------------------------------------------------------------");
						printf("\nOdaberite opciju: ");
						pom = choose_event(head, choose_from_menu(h));
						printf("\n================================================================================\n\n");
						do
						{
							printf("\n1.Dodavanje komentara 2.Pregled komentara 3.Brisanje komentara\n4.Nazad");
							printf("\n--------------------------------------------------------------------------------");
							printf("\nOdaberite opciju: ");
							g = choose_from_menu(4);
							printf("\n================================================================================\n\n");
							if (g == 1)
							{
								add_comment(pom->info.name);
							}
							else if (g == 2)
							{
								print_comments(pom->info.name);
								printf("\nPritisnite Enter.\n");
								fgets(trash, 201, stdin);
							}
							else if (g == 3)
							{
								delete_comment(pom->info.name);
							}
							else if (g == 4)
								trg1 = 1;
						} while (!trg1);
					}
				}
				else if (x == 6)
					trg = 1;
			} while (!trg);
		}
		else if (y == 3)
			printf("Kraj!\n");

	}

	while (y == 1 || y == 2);

	push_to_folder(head);

    return 0;
}
