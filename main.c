#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char oznacenie;   // Veľké písmeno z intervalu <A, Z>
    int cislovanie;   // Číslo z intervalu <000, 999>
    char druh;        // Malé písmeno z intervalu <a, z>
} ID_mer_modulu;

typedef struct {
    ///double краще зробити
    char latitude[9];   // Reálne číslo pre zemepisnú šírku
    char longitude[9];  // Reálne číslo pre zemepisnú dĺžku
} Pozicia_modulu;

typedef struct dani{
    ID_mer_modulu id;
    Pozicia_modulu poz;
    char typ[3];
    char hod[7];
    char cas[5];
    char dat[9];
    struct dani *dalsi;
}DANI;
void uvolni(DANI *head);


void n(FILE **f,DANI **head,int *count){

    if(*head!=NULL) {
        printf("Štruktúry už boli vytvorené\n");
        while (*head != NULL) {//checks if the list has already been created. if yes, then deletes old records
            DANI *temp = *head;
            *head = (*head)->dalsi;
            free(temp);
        }
    }

    if ((*f = fopen("dataloger_V2.txt", "r+")) == NULL) {//checks whether the file has been created
        printf("Zaznamy neboli nacitane!\n");
        return;
    }


    char line[100];

    int countzap=0;
    while (fgets(line,sizeof(line),*f) != NULL){
        if (strcmp(line,"$$$\n")==0){
            countzap++;
        }
    }
    *count=countzap;

    rewind(*f);

    while (fgets(line,sizeof(line),*f) != NULL){
        if (line[0] == '\n'|| strcmp(line, "$$$\n") == 0) {
//            printf("\n");
            continue;  // Skips empty lines
        }
        DANI *new_record = (DANI *)malloc(sizeof(DANI));
        if (new_record == NULL) {
            perror("Chyba pri prideľovaní pamäte");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%c %3d %c", &new_record->id.oznacenie, &new_record->id.cislovanie, &new_record->id.druh);

        fgets(line, sizeof(line), *f);
        sscanf(line, "%8s%8s", new_record->poz.latitude, new_record->poz.longitude);


        fgets(line,sizeof(line),*f);
        sscanf(line, "%3s", new_record->typ);

        fgets(line,sizeof(line),*f);
        sscanf(line, "%7s", new_record->hod);

        fgets(line,sizeof(line),*f);
        sscanf(line, "%5s", new_record->cas);

        fgets(line,sizeof(line),*f);
        sscanf(line, "%9s", new_record->dat);



//        printf("ID. mer. modulu: %c%3d%c\n", new_record->id.oznacenie, new_record->id.cislovanie, new_record->id.druh);
///        printf("Pozícia modulu: +%7.4lf+%7.4lf\n", new_record->poz.latitude, new_record->poz.longitude);
//        printf("Pozícia modulu: %s %s\n", new_record->poz.latitude, new_record->poz.longitude);
//        printf("Typ mer. veliciny: %s\n", new_record->typ);
//        printf("Hodnota: %s\n", new_record->hod);
//        printf("Cas merania: %s\n", new_record->cas);
//        printf("Datum merania: %s\n", new_record->dat);

        new_record->dalsi = *head;
        *head = new_record;

    }

    if ((*count) > 0) {
        printf("Nacitalo sa <%d> zaznamov\n", *count);
    }
}

void v(DANI *head,int count) {
    DANI *current = head;
    int k=1;

    if (count!=0) {
        while (current != NULL) {
            printf("%d:\n", k);
            k++;
            printf("ID: %c%3d%c\t%s\t%s\n", current->id.oznacenie, current->id.cislovanie, current->id.druh,
                   current->typ, current->hod);
            printf("Poz: %s\t%s\n", current->poz.latitude, current->poz.longitude);
            printf("DaC: %s\t%s\n", current->dat, current->cas);

            current = current->dalsi;
        }
    }

}

void p(DANI **head,int *count) {
    int pozicia;
    printf("ake cislo:");
    scanf("%d", &pozicia);

    DANI *new_record = (DANI *) malloc(sizeof(DANI));
    if (new_record == NULL) {
        perror("Chyba pri prideľovaní pamäte");
        exit(EXIT_FAILURE);
    }

    char idn[6];
    char pozn[15];
    char typn[3];
    char hodn[7];
    char casn[5];
    char datn[9];


    printf("Enter ID (up to 5 characters): ");
    scanf("%5s", idn);
    sscanf(idn, "%c%d%c", &new_record->id.oznacenie, &new_record->id.cislovanie, &new_record->id.druh);



    printf("Enter Position (up to 14 characters): ");
    scanf("%14s", pozn);

    //форматуєм в запис якій нам потрібне
    char part1[8];
    char part2[8];
    double num;

    sscanf(pozn,"%7s%7s", part1, part2);//розділяюмо на дві частини

    num = atof(part1);
    num/=10000;//робим точку після 2 цифр
    sprintf(new_record->poz.latitude, "+%.4lf", num);//правильно записуємо

    num = atof(part2);
    num/=10000;
    sprintf(new_record->poz.longitude, "+%.4lf", num);
    //


    printf("Enter Type (up to 2 characters): ");
    scanf("%2s", typn);
    strcpy(new_record->typ, typn);


    printf("Enter Value (up to 6 characters): ");
    scanf("%6s", hodn);
    strcpy(new_record->hod, hodn);

    printf("Enter Time (up to 4 characters): ");
    scanf("%4s", casn);
    strcpy(new_record->cas, casn);

    printf("Enter Date (up to 8 characters): ");
    scanf("%8s", datn);
    strcpy(new_record->dat, datn);


    //
    printf("\n");
    printf("ID: %c%3d%c\t%s\t%s\n", new_record->id.oznacenie, new_record->id.cislovanie, new_record->id.druh,
           new_record->typ, new_record->hod);
    printf("Poz: %s\t%s\n", new_record->poz.latitude, new_record->poz.longitude);
    printf("DaC: %s\t%s\n", new_record->dat, new_record->cas);
    printf("\n");
    // Виведення результатів
    printf("ID: %s\n", idn);
    printf("Poz: %s\n", pozn);
    printf("Typ: %s\n", typn);
    printf("Hod: %s\n", hodn);
    printf("Cas: %s\n", casn);
    printf("Dat: %s\n", datn);

    // Вставка нового запису на певне місце
    if (pozicia == 1 || *head == NULL) {
        // Вставка в початок списку
        new_record->dalsi = *head;
        *head = new_record;
    } else {
        // Вставка в середину списку
        DANI *current = *head;
        int i=1;

        while (current!=NULL&&i<pozicia-1){
            current = current->dalsi;
            i++;
        }

        if(current!=NULL){
            new_record->dalsi=current->dalsi;
            current->dalsi=new_record;
        }else{
            // Якщо вказана позиція більша за кількість елементів у списку, вставте в кінець
            while (current->dalsi!=NULL){
                current=current->dalsi;
            }
            new_record->dalsi=NULL;
            current->dalsi=new_record;
        }

    }
    (*count)++;
}

void uvolni(DANI *head){
    DANI *current = head;
    DANI *next;

    while (current != NULL) {
        next = current->dalsi;
        free(current);
        current = next;
    }
}

int main() {
    FILE *f=NULL;
    DANI *head=NULL;
    char option;
    int m=1;
    int count=0;
    while (m) {
        scanf("%c", &option);

        if (option == 'n') {
            n(&f,&head,&count);
        }
        if (option == 'v') {
            v(head,count);
        }
        if (option == 'p') {
            p(&head,&count);
        }
        if (option == 'k') {
            fclose(f);
            uvolni(head);
            m=0;
        }
    }
    return 0;
}