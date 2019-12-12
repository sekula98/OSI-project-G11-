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

int main()
{
    char kor_ime[50],kor_sifra[50],user[50],pass[50],c;
    int i;
    int dozvola=0;
    citanje_podataka(user,pass);
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




}
