#include <stdio.h>
#include <string.h>

int verifica_siruri(char *sir1, char *sir2);

int conectare_de_modul(char *prim_sir, char *sir_doi){
    // functia verifica daca in al vom avea 0 sau 1 si returneaza rezultatul corespunzator in urma apelarii functiei verifica_siruri din modulul siruri.asm.
    
    char intermediar[100];
    char ok;
    int k = 0;

    strcpy(intermediar, prim_sir);  // in intermediar vom pune primul sir pentru a nu modifica ceea ce avem memorat in primul sir prim_sir
    verifica_siruri(intermediar, sir_doi);
    
    __asm mov [ok], al  // in variabila ok vom pune valoarea din al pentru a o verifica mai tarziu


    if (ok)
        k = 1;  // daca ok este 1 atunci vom memora valoarea 1 in k, iar in caz contrar valoarea 0 din k nu va fi modificata
    
    return k;   // vom returna k in care avem stocat 0 daca in al doilea sir(sir_doi) nu se gaseste primul sir(prim_sir) ca si subsir, iar 1 in caz contrar
}

int main(){

    char sir1[100], sir2[100], ver[5];
    int check = 1;
    strcpy(ver, "0");

    //  vom citi primul sir
    printf("Introdu primul sir de caractere: ");
    scanf("%s", sir1);

    //  vom citi al doilea sir
    printf("Introdu urmatorul sir de caractere: ");
    scanf("%s", sir2);

    //  vom verifica daca sirul se incheie, astfel 0 reprezentand cheia de terminare a citirii noilor siruri
    while ((strcmp(sir2,ver)) != 0)
    {
        if(conectare_de_modul(sir1, sir2) == 0)
            check = 0;                              //  daca din conectare_de_modul(sir1,sir2) vom primi valoarea 0 in check vom pune tot 0, iar altfel in check va ramane valoarea 1.

        //  citim un nou sir
        printf("Introdu urmatorul sir de caractere: ");
        scanf("%s", sir2);
    }

    //  in functie de valoarea lui check vom afisa pentru utilizator mesajul corespunzator
    if (check == 1)
        printf("Primul sir se afla in celelalte siruri.");
    else
        printf("Primul sir nu se afla in celelalte siruri.");
    
    return 0;
}