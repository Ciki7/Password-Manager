#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

int isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

int isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int hasLowerCase(const char* password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isLower(password[i])) {
            return 1;
        }
    }
    return 0;
}

int hasUpperCase(const char* password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isUpper(password[i])) {
            return 1;
        }
    }
    return 0;
}

void displayDescription() {
    printf("\n=== Password Manager ===\n");
    printf("Password Manager je aplikacija koja Vam pomaze upravljanjem vasim lozinkama.\n");
    printf("Program omogucuje skladistenje lozinki korisnickih racuna.\n");
    printf("===================================\n");
    printf(" ");
}


void displayInstructions() {
    printf("\n=== Upute za koristenje ===\n");
    printf("1. Pregled sifri: Prikazuje sve spremljene sifre.\n");
    printf("2. Dodavanje sifri: Omogucuje unos novog korisnickog racuna i lozinke.\n");
    printf("3. Random generiranje sifri: Generira nasumicnu lozinku ili postavlja parametre za generiranje.\n");
    printf("4. Uredivanje sifri: Omogucuje promjene postojecih lozinski.\n");
    printf("5. Brisanje sifri: Brisanje postojecih lozinki\n");
    printf("6. Mijenjanje master sifre: Omogucuje promjenu glavne lozinke za pristup programu.\n");
    printf("7. Pomoc: Prikazuje ovaj izbornik s uputama.\n");
    printf("0. Izlaz: Izlazi iz programa.\n");
    printf("===================================\n");

}

void displaySubmenuAddPassword() {
    printf("----- Podmeni - Dodavanje sifri -----\n");
    printf("Unesite ime korisnickog racuna: ");
    char name[100];
    scanf("%s", name);

    printf("Unesite lozinku koju zelite dodati: ");
    char password[100];
    scanf("%s", password);

    int hasLower = hasLowerCase(password);
    int hasUpper = hasUpperCase(password);
    int hasDigit = 0;
    int hasSpecial = 0;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isDigit(password[i])) {
            hasDigit = 1;
        }
        else {
            hasSpecial = 1;
        }
    }

    if (hasLower && hasUpper && hasDigit && hasSpecial) {
        ACCOUNT account;
        strcpy(account.name, name);
        strcpy(account.password, password);

        printf("Korisnicki racun i lozinka uspjesno dodani.\n");
    }
    else {
        printf("Lozinka nije zadovoljila sigurnosne uvjete.\n");
    }

    printf("===================================\n");
}



//void displaySubmenuViewPasswords() {
//    printf("----- Podmeni - Pregled sifri -----\n");
//    printf("1. Ispis svih spremljenih sifri\n");
//    printf("2. Pretrazivanje sifri\n");
//    printf("0. Povratak na glavni izbornik\n");
//    printf("----------------------------------\n");
//}
//
//

