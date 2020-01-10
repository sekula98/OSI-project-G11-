#include "user_funkcije.h"
#include "user_funkcije.c"
int main()

{
    NODE* head = NULL;
    NODE* pom = NULL;
    pull_from_folder(&head);
    int trg=0,x,y;
    char trash[100];

    print_hello();
    printf("\n\nPritisnite Enter.\n");
    fgets(trash, 101, stdin);
    printf("\n\n\n\n");

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
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_all_events_info(head);
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==2)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.\n");
                        getchar();
                    }
                    else
                    {
                        print_today_events(head);
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                }

                if (x==5)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_event_from_category(head);
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==3)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_future_events(head);
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                }
                if(x==4)
                {
                    if(list_is_empty(head))
                    {
                        printf("\nLista dogadjaja je prazna!\n");
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                    else
                    {
                        print_past_events(head);
                        printf("\n\nPritisnite Enter.\n");
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
                printf("\n\nPritisnite Enter.\n");
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
                        add_comment(pom->info.name);
                        printf("\n\nPritisnite Enter.\n");
                        fgets(trash, 101, stdin);
                    }
                    if(g==2)
                    {
                        print_comments(pom->info.name);
                        printf("\n\nPritisnite Enter.\n");
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
            printf("\nOdaberi opciju: ");
            int l=choose_from_menu(2);
            if(l==1)
                quiz();
            if(l==2)
            {
                printf("\n\nPritisnite Enter.\n");
                fgets(trash, 101, stdin);
            }
        }
        if(y==4)
        {
            trg=1;
            printf("KRAJ!\n");
        }
    }
    while(!trg);
}





