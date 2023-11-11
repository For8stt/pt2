#include <stdio.h>

int main() {
    FILE *f;
    if((f=fopen("dataloger_V2.txt","w+"))==NULL){
        printf("Nepodarilo otvorit");

    } else{
        printf("otvorilo subor");
    }
    fclose(f);

    return 0;
}

