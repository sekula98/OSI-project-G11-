#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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
void kreiranje_def_kat(FILE*f4)
{
//    f1=fopen("izlozbe.txt","a");
//    fclose(f1);
//    f2=fopen("koncerti.txt","a");
//    fclose(f2);
//    f3=fopen("promocije.txt","a");
//    fclose(f3);
//    f4=fopen("imena_kat.txt","a");
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
void dodavanje_kategorije(FILE*imena_kat)
{
    char nova_kategorija[50];
    printf("Unesite ime nove kategorije\n");
    getchar();
    fgets(nova_kategorija,51,stdin);
    imena_kat=fopen("imena_kat.txt","a");//upisuje imena kategorija u datoteku
    fprintf(imena_kat,"%s",nova_kategorija);//
    fclose(imena_kat);
}
void prikaz_kategorija(FILE*imena_kat)
{
    char ispis_kat[50];
    imena_kat=fopen("imena_kat.txt","r");
    if(imena_kat)
    {
        while(fgets(ispis_kat,51,imena_kat))
        {
            printf("%s",ispis_kat);
        }
    }
    fclose(imena_kat);
}
void brisanje_kategorije(FILE*imena_kat)
{
    int i,j,o;
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
        scanf("%d",&j);
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
int main()
{
    char kor_ime[50],kor_sifra[50],user[50],pass[50];
    int i=0,x;
    int dozvola=0;
    FILE*imena_kat;
    citanje_podataka(user,pass);
    kreiranje_def_kat(imena_kat);
    do
    {
        printf("Unesi ime\n");
        scanf("%s",kor_ime);
        printf("Unesi sifru\n");
        unos_kor_sifre(kor_sifra);

        if(!strcmp(kor_ime,user))
        {
            if(!strcmp(kor_sifra,pass))
            {
                dozvola=1;
                printf("Dobro dosli %s\n",kor_ime);
            }
            else
                printf("Sifra nije tacna\n");
        }
        else
            printf("Korisnicko ime nije tacno\n");
    }
    while(!dozvola);
    do
    {
        printf("\nIzaberite: 1.Dodaj novu kategoriju. 2.Prikazi postojece kategorije. 3.Obrisi kategoriju. 4.Kraj\n");
        scanf("%d",&x);
        if(x==1)
        {
            dodavanje_kategorije(imena_kat);
        }

        if (x==2)
        {
            prikaz_kategorija(imena_kat);
        }
        if(x==3)
        {
            brisanje_kategorije(imena_kat);
        }

        if (x==4)
        {
            printf("Kraj");
        }
    }

    while(x==1||x==2||x==3);





}
