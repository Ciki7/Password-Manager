#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "header.h"



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


void addPassword(PASSWORD passwords[], int* numPasswords) {
    if (*numPasswords == MAX_PASSWORDS) {
        printf("Baza sifri je puna. Nije moguce dodati sifru.\n");
        return;
    }

    PASSWORD newPassword;

    printf("Unesite username: ");
    scanf("%s", newPassword.username);

    int validPassword = 0;

    while (!validPassword) {
        printf("Unesite sifru: ");
        scanf("%s", newPassword.password);

        int hasUppercase = 0;
        int hasLowercase = 0;
        int hasDigit = 0;
        int hasSymbol = 0;

        for (int i = 0; newPassword.password[i] != '\0'; i++) {
            if (isupper(newPassword.password[i])) {
                hasUppercase = 1;
            }
            else if (islower(newPassword.password[i])) {
                hasLowercase = 1;
            }
            else if (isdigit(newPassword.password[i])) {
                hasDigit = 1;
            }
            else {
                hasSymbol = 1;
            }
        }

        if (hasUppercase && hasLowercase && hasDigit && hasSymbol) {
            validPassword = 1;
        }
        else {
            printf("Sifra ne zadovoljava uvjete: malo slovo, veliko slovo, broj i znak. Pokusajte ponovno\n");
        }
    }

    passwords[*numPasswords] = newPassword;
    (*numPasswords)++;

    FILE* file = fopen("passwords.txt", "a");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za pisanje.\n");
        return;
    }

    fprintf(file, "%s %s\n", newPassword.username, newPassword.password);
    fclose(file);

    printf("Sifra uspjesno dodana\n");
}

void savePasswords(PASSWORD passwords[], int numPasswords) {
    FILE* file = fopen("passwords.txt", "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    for (int i = 0; i < numPasswords; i++) {
        fprintf(file, "%s %s\n", passwords[i].username, passwords[i].password);
    }

    fclose(file);

    printf("Lozinke su uspjesno spremljene u datoteku.\n");
}

void displayPasswords() {
    FILE* file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za citanje.\n");
        return;
    }

    PASSWORD password;
    printf("Spremljene lozinke:\n");
    while (fscanf(file, "%s %s", password.username, password.password) == 2) {
        printf("Korisnicko ime: %s\n", password.username);
        printf("Lozinka: %s\n", password.password);
        printf("------------------------------\n");
    }

    fclose(file);
}

void findPassUsername(const PASSWORD passwords[], int numPasswords, const char* username) {
    int found = 0;

    for (int i = 0; i < numPasswords; i++) {
        if (strcmp(passwords[i].username, username) == 0) {
            printf("Korisnicko ime: %s, Lozinka: %s\n", passwords[i].username, passwords[i].password);
            found = 1;
        }
    }

    if (!found) {
        printf("Sifra s korisnickim imenom '%s' nije pronadena.\n", username);
    }
}


void loadPasswords(PASSWORD passwords[], int* numPasswords) {
    FILE* file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za čitanje.\n");
        return;
    }

    *numPasswords = 0;
    while ((*numPasswords) < MAX_PASSWORDS && fscanf(file, "%s %s", passwords[*numPasswords].username, passwords[*numPasswords].password) == 2) {
        (*numPasswords)++;
    }

    fclose(file);
}

void editPassword(PASSWORD passwords[], int numPasswords) {
    loadPasswords(passwords, &numPasswords);

    if (numPasswords == 0) {
        printf("Nema spremljenih sifri.\n");
        return;
    }

    char username[100];
    int nadenIndex = -1;

    while (nadenIndex == -1) {
        printf("Unesite korisnicko ime za uredivanje: ");
        scanf("%s", username);

        for (int i = 0; i < numPasswords; i++) {
            if (strcmp(passwords[i].username, username) == 0) {
                nadenIndex = i;
                break;
            }
        }

        if (nadenIndex == -1) {
            printf("Sifra s korisnickim imenom '%s' nije pronadena.\n", username);
        }
    }

    printf("Unesite novu lozinku: ");
    scanf("%s", passwords[nadenIndex].password);

    savePasswords(passwords, numPasswords);

    printf("Lozinka uspjesno uredena i spremljena.\n");
}


void requestMasterPassword() {
    if (!isMasterPasswordSet()) {
        char password[MASTER_PASSWORD_LENGTH];
        printf("Ne postoji master sifra. Molimo odaberite master sifru: ");
        scanf("%s", password);
        setMasterPassword(password);
        printf("Master sifra uspjesno dodana.\n");
    }
    else {
        char password[MASTER_PASSWORD_LENGTH];
        printf("Enter master password: ");
        scanf("%s", password);

        if (validateMasterPassword(password)) {
            printf("Master sifra tocno unesena, pristup odobren.\n");
        }
        else {
            printf("Master sifra krivo unesena, odbijen pristup..\n");
            exit(1);
        }
    }
}

int isMasterPasswordSet() {
    FILE* file = fopen(MASTER_PASSWORD_FILE, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void setMasterPassword(const char* password) {
    FILE* file = fopen(MASTER_PASSWORD_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%s", password);
        fclose(file);
    }
    else {
        printf("Nije uspjesan unos master sifre.\n");
        exit(1);
    }
}

int validateMasterPassword(const char* password) {
    FILE* file = fopen(MASTER_PASSWORD_FILE, "r");
    if (file != NULL) {
        char storedPassword[MASTER_PASSWORD_LENGTH];
        fscanf(file, "%s", storedPassword);
        fclose(file);
        return strcmp(password, storedPassword) == 0;
    }
    return 0;
}

void changeMasterPassword() {
    if (!isMasterPasswordSet()) {
        printf("Master sifra ne postoji. Odaberite master sifru:.\n");
        return;
    }

    char currentPassword[MASTER_PASSWORD_LENGTH];
    printf("Unesite trenutnu master sifru: ");
    scanf("%s", currentPassword);

    if (validateMasterPassword(currentPassword)) {
        char newPassword[MASTER_PASSWORD_LENGTH];
        printf("Unesite novu master sifru: ");
        scanf("%s", newPassword);

        setMasterPassword(newPassword);
        printf("Master sifra uspjesno promijenjena.\n");
    }
    else {
        printf("Pogresno unesena master sifra. Pristup odbijen.\n");
    }
}
