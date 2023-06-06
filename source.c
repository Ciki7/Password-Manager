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
    printf("0. Povratak na glavni izbornik\n");
    printf("--------------------------------------\n");
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
    printf("1. Promjena master sifre\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("---------------------------------------------\n");
}

void displaySubmenuHelp() {
    printf("----- Podmeni - Pomoc -----\n");
    printf("1. Opis programa\n");
    printf("2. Upute koristenja\n");
    printf("0. Povratak na glavni izbornik\n");
    printf("----------------------------\n");
}

int main() {
    requestMasterPassword();
    PASSWORD passwords[MAX_PASSWORDS];
    int numPasswords = 0;
    int choice;
    int subChoice;

    do {
        printf("=========== Password Manager ===========\n");
        printf("1. Pregled sifri\n");
        printf("2. Dodavanje sifri\n");
        printf("3. Uredivanje sifri\n");
        printf("4. Brisanje sifri\n");
        printf("5. Mijenjanje master sifre\n");
        printf("6. Pomoc\n");
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
            switch (subChoice) {
            case 1:
                displayPasswords(passwords, numPasswords);
                break;
            case 2: {
                char username[100];
                printf("Unesite korisnicko ime: ");
                scanf("%s", username);
                findPassUsername(passwords, numPasswords, username);
                break;
            }
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
            break;
        case 2:
            printf("Dodavanje sifri\n");
            displaySubmenuAddPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            switch (subChoice) {
            case 1:
                addPassword(passwords, &numPasswords);
                break;
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
            break;
        case 3:
            printf("Uredivanje sifri\n");
            displaySubmenuEditPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            switch (subChoice) {
            case 1:
                editPassword(passwords, numPasswords);
                break;
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
            break;
        case 4:
            printf("Brisanje sifri\n");
            displaySubmenuDeletePassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            switch (subChoice) {
            case 1:
                deletePassword(passwords, &numPasswords);
                break;
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
            break;
        case 5:
            printf("Mijenjanje master sifre\n");
            displaySubmenuChangeMasterPassword();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            switch (subChoice) {
            case 1:
                changeMasterPassword();
                break;
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
            break;
        case 6:
            printf("Pomoc\n");
            displaySubmenuHelp();
            printf("Unesite podizbor: ");
            scanf("%d", &subChoice);
            switch (subChoice) {
            case 1:
                displayDescription();
                break;
            case 2:
                displayInstructions();
                break;
            case 0:
                break;
            default:
                printf("Nepoznata opcija. Molimo odaberite ponovno.\n");
                break;
            }
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
