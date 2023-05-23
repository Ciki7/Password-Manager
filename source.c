#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

void displaySubmenuViewPasswords() {
    printf("----- Podmeni - Pregled sifri -----\n");
    printf("1. Ispis svih spremljenih sifri\n");
    printf("2. Pretrazivanje sifri\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("----------------------------------\n");
}

void displaySubmenuAddPassword() {
    printf("----- Podmeni - Dodavanje sifri -----\n");
    printf("1. Unos novog korisnickog racuna\n");
    printf("2. Unos dodatnih informacija o racunu\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("--------------------------------------\n");
}

void displaySubmenuGeneratePassword() {
    printf("----- Podmeni - Random generiranje sifri -----\n");
    printf("1. Generiranje nasumicne lozinke\n");
    printf("2. Postavljanje parametara za generiranje\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("----------------------------------------------\n");
}

void displaySubmenuEditPassword() {
    printf("----- Podmeni - Uredivanje sifri -----\n");
    printf("1. Odabir postojeces sifre za uredivanje\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("----------------------------------------\n");
}

void displaySubmenuDeletePassword() {
    printf("----- Podmeni - Brisanje sifri -----\n");
    printf("1. Odabir postojeces sifre za brisanje\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("-------------------------------------\n");
}

void displaySubmenuChangeMasterPassword() {
    printf("----- Podmeni - Mijenjanje master sifre -----\n");
    printf("1. Promjena glavne lozinke za pristup\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("---------------------------------------------\n");
}

void displaySubmenuHelp() {
    printf("----- Podmeni - Pomoc -----\n");
    printf("1. Upute koristenja\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("----------------------------\n");
}

int main() {
    int choice;
    int subChoice;

    do {
        printf("=========== Password Manager ===========\n");
        printf("1. Pregled sifri\n");
        printf("2. Dodavanje sifri\n");
        printf("3. Random generiranje sifri\n");
        printf("4. Uredivanje sifri\n");
        printf("5. Brisanje sifri\n");
        printf("6. Mijenjanje master sifre\n");
        printf("7. Pomoc\n");
        printf("0. Izlaz\n");
        printf("========================================\n");
        printf("Vas izbor: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Pregled sifri\n");
            displaySubmenuViewPasswords();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            
            break;
        case 2:
            printf("Dodavanje sifri\n");
            displaySubmenuAddPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            
            break;
        case 3:
            printf("Random generiranje sifri\n");
            displaySubmenuGeneratePassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            
            break;
        case 4:
            printf("Uredivanje sifri\n");
            displaySubmenuEditPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
          
            break;
        case 5:
            printf("Brisanje sifri\n");
            displaySubmenuDeletePassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            
            break;
        case 6:
            printf("Mijenjanje master sifre\n");
            displaySubmenuChangeMasterPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
           
            break;
        case 7:
            printf("Pomoc\n");
            displaySubmenuHelp();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
           
            break;
        case 0:
            printf("Izlaz\n");
            break;
        default:
            printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
            break;
        }

    } while (choice != 0);

    return 0;
}


