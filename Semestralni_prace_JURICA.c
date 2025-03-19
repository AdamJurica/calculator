#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DELKA_NACTENEHO_RETEZCE 30
#define IDENTIFIKATOR_CHYBY 1000
#define FILE_NAME "vysledky.txt"


void vycistit_buffer()
{
  while (getchar() != '\n');
}


double get_double()
{
  char zadany_retezec[DELKA_NACTENEHO_RETEZCE];
  char *zbytek;
  double cislo;

  while(1) {
    if (scanf("%s", zadany_retezec) == 0) {
      printf("\nHodnota musi byt kladne a nenulove cislo, zkuste to znovu: ");
      while (getchar() != '\n');
      continue;
    }

    while (getchar() != '\n');

    cislo = strtod(zadany_retezec, &zbytek); //Postup zvolen kvuli problemum pri pouziti carky ve vyjadreni desetinneho cisla
    if (cislo != 0 && cislo > 0) break;
    printf("Hodnota musi byt kladne a nenulove cislo, zkuste to znovu: ");
  }
  return cislo;
}


double vypocet(FILE *fp, char volba, double p1, double p2, double q1, double q2)
{
  if(q1 != 0 && q2 != 0 && p1 != 0 && p2 != 0 && p1 != p2 && q1 != q2) {
    int znamenko;
    if(volba == 'a')
      znamenko = -1;
    else
      znamenko = 1;
    double vysledek = ((znamenko*(q2-q1) / ((q2+q1)/2))  /  ((p2-p1) / ((p2+p1)/2)));

    //zapis do souboru
    fprintf(fp, "Q1 = %lf\n", q1);
    fprintf(fp, "Q2 = %lf\n", q2);
    fprintf(fp, "P1 = %lf\n", p1);
    fprintf(fp, "P2 = %lf\n", p2);
    fprintf(fp, "Vypoctena elasticita = %lf", vysledek);
    return vysledek;
  } else {
    printf("Neznama chyba!");
    return IDENTIFIKATOR_CHYBY;
  }
}


void clear()
{
  system("cls");
}


char *vysvetleni(double vysledek)
{
  if (vysledek < 0) return("\nElasticita je zaporna, jedna se tedy o Giffenuv paradox.");
  else if (vysledek == 1) return("\nNabidka/poptavka je jednotkove elasticka.");
  else if (vysledek == 0) return("\nNabidka/poptavka je dokonale neelasticka.");
  else if (vysledek < 1) return("\nNabidka/poptavka je neelasticka.");
  else if (vysledek > 1) return("\nNabidka/poptavka je elasticka.");
  else return("Je to jinak.");
}

int main()
{
  FILE *fp;
  if((fp = fopen(FILE_NAME, "a")) == NULL) printf("Nepodarilo se otevrit soubor %s!", FILE_NAME);
  const int SLEEP_TIME = 1000;
  while(1) {
    char volba_1, volba_2;
    double vysledek;

    printf("****************** Semestralni prace ******************\n");
    printf("********************* Adam Jurica *********************\n\n");
    printf("Kalkulacka cenove elasticity poptavky a nabidky\n\n");
    printf("'a' - Vypocet elasticity poptavky\n");
    printf("'b' - Vypocet elasticity nabidky\n");
    printf("'c' - Ukonceni programu\n\n");
    printf("Pri zadavani desetinnych cisel pouzivejte tecku!!!\n\n");

    printf("Zadejte svou volbu: ");
    volba_1 = getchar();
    vycistit_buffer();
    printf("\t\t\t\tVase volba: %c\n\n", volba_1);

    switch(volba_1) {
      case 'A':
      case 'a':
      case 'B':
      case 'b':
        printf("Zadejte mnozstvi Q1: ");
        double q1 = get_double();
        printf("\t\t\t\tZadali jste: %.2lf\n", q1);

        printf("Zadejte mnozstvi Q2: ");
        double q2 = get_double();
        printf("\t\t\t\tZadali jste: %.2lf\n", q2);

        printf("Zadejte cenu P1: ");
        double p1 = get_double();
        printf("\t\t\t\tZadali jste: %.2lf\n", p1);

        printf("Zadejte cenu P2: ");
        double p2 = get_double();
        printf("\t\t\t\tZadali jste: %.2lf\n", p2);

        vysledek = vypocet(fp, volba_1, p1, p2, q1, q2);
        if(vysledek == IDENTIFIKATOR_CHYBY) break;
        printf("\nVypoctena elasticita: %.2lf", vysledek);
        break;
      case 'C':
      case 'c':
        if((fclose(fp)) == EOF) printf("Nepodarilo se zavrit soubor %s!", FILE_NAME);
        return 0;
      default:
        printf("Zadali jste nepovoleny znak!");
        Sleep(SLEEP_TIME);
        clear();
        continue;
    }

    //Vysvetleni a jeho zapis do souboru
    char *vysvetlivka = vysvetleni(vysledek);
    printf("\n%s\n",vysvetlivka);
    fprintf(fp, "%s\n---------------\n", vysvetlivka);

    //OPAKOVANI
    printf("\n\nPro novy vypocet zadejte 'a', program ukoncite libovolnym jinym znakem\n");
    printf("Zadejte svou volbu: ");
    volba_2 = getchar();
    vycistit_buffer();

    if(volba_2 == 'a' || volba_2 == 'A')
      clear();
    else
      break;
  }
  if((fclose(fp)) == EOF) printf("Nepodarilo se zavrit soubor %s!", FILE_NAME);
  return 0;
}

