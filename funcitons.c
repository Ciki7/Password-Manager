#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    printf("SIFRE OBAVEZNO MORAJU SADRZAVATI MALO SLOVO; VELIKO SLOVO, BROJ I ZNAK.\n");
    printf("===================================\n");
}


void addPassword(PASSWORD passwords[], int* numPasswords) {
    char* username = (char*)malloc(100 * sizeof(char));
    char* password = (char*)malloc(100 * sizeof(char));

    if (username == NULL || password == NULL) {
        printf("Greska: Neispravni parametri.\n");
        free(username);
        free(password);
        return;
    }

    printf("Unesite korisnicko ime: ");
    scanf("%s", username);

    int validPassword = 0;

    while (!validPassword) {
        printf("Unesite sifru: ");
        scanf("%s", password);

        int hasUppercase = 0;
        int hasLowercase = 0;
        int hasDigit = 0;
        int hasSymbol = 0;

        for (int i = 0; password[i] != '\0'; i++) {
            if (isupper(password[i])) {
                hasUppercase = 1;
            }
            else if (islower(password[i])) {
                hasLowercase = 1;
            }
            else if (isdigit(password[i])) {
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
            printf("Sifra ne zadovoljava uvjete: malo slovo, veliko slovo, broj i znak. Pokusajte ponovno.\n");
        }
    }

    FILE* file = fopen("passwords.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Greska pri otvaranju datoteke: %s\n", strerror(errno));
        free(username);
        free(password);
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Sifra uspjesno dodana.\n");

    free(username);
    free(password);
}

void savePasswords(const PASSWORD* passwords, int numPasswords) {
    FILE* file = fopen("passwords.txt", "w");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke\n");
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

    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    fseek(file, 0, SEEK_SET);

    PASSWORD* passwords = NULL;
    int numPasswords = 0;
    PASSWORD password;

    while (fscanf(file, "%s %s", password.username, password.password) == 2) {
        passwords = realloc(passwords, (numPasswords + 1) * sizeof(PASSWORD));
        passwords[numPasswords] = password;
        numPasswords++;
    }

    fclose(file);

    qsort(passwords, numPasswords, sizeof(PASSWORD), comparePasswords);

    printf("Spremljene lozinke:\n");
    for (int i = 0; i < numPasswords; i++) {
        printf("Korisnicko ime: %s\n", passwords[i].username);
        printf("Lozinka: %s\n", passwords[i].password);
        printf("------------------------------\n");
    }

    free(passwords);
}
void searchPasswords(const char* username) {
    FILE* file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za citanje.\n");
        return;
    }

    PASSWORD password;
    int found = 0;

    while (fscanf(file, "%s %s", password.username, password.password) == 2) {
        if (strcmp(password.username, username) == 0) {
            printf("Korisnicko ime: %s, Lozinka: %s\n", password.username, password.password);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Lozinka s korisnickim imenom '%s' nije pronadena.\n", username);
    }
}

void editPassword(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za citanje i pisanje.\n");
        return;
    }

    char username[100];
    printf("Unesite korisnicko ime za uredivanje: ");
    scanf(" %99[^\n]", username);

    PASSWORD password;
    int found = 0;

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Nije moguce otvoriti privremenu datoteku za pisanje.\n");
        fclose(file);
        return;
    }

    char newPassword[100];
    printf("Unesite novu lozinku: ");
    scanf(" %99s", newPassword);

    while (fscanf(file, "%s %s", password.username, password.password) == 2) {
        if (strcmp(password.username, username) == 0) {
            int validPassword = 0;

            while (!validPassword) {
                if (strcmp(newPassword, password.password) == 0) {
                    printf("Nova lozinka ne smije biti ista kao stara lozinka.\n");
                    printf("Unesite novu lozinku: ");
                    scanf(" %99s", newPassword);
                }
                else if (!validatePassword(newPassword)) {
                    printf("Nova lozinka ne zadovoljava uvjete (malo slovo, veliko slovo, broj, znak). Molimo unesite ponovno: ");
                    scanf(" %99s", newPassword);
                }
                else {
                    validPassword = 1;
                }
            }

            fprintf(tempFile, "%s %s\n", password.username, newPassword);
            found = 1;
        }
        else {
            fprintf(tempFile, "%s %s\n", password.username, password.password);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    if (found) {
        printf("Lozinka uspjesno uredena.\n");
    }
    else {
        printf("Sifra s korisnickim imenom '%s' nije pronadena.\n", username);
    }
}

void requestMasterPassword() {
    if (!isMasterPasswordSet()) {
        char password[MASTER_PASSWORD_LENGTH];
        printf("Ne postoji master sifra. Molimo odaberite master sifru: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        setMasterPassword(password);
        printf("Master sifra uspjesno dodana.\n");
    }
    else {
        char password[MASTER_PASSWORD_LENGTH];
        int attempts = 3;  

        while (attempts > 0) {
            printf("Unesite master sifru (%d pokusaja): ", attempts);
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            if (validateMasterPassword(password)) {
                printf("Pristup odobren.\n");
                return;  
            }
            else {
                printf("Pristup odbijen.\n");
                attempts--;
            }
        }

        printf("Dostigli ste maksimalan broj pogresnih pokusaja. Izlaz iz aplikacije.\n");
        exit(1);  
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
        printf("Master sifra ne postoji. Odaberite master sifru:\n");
        return;
    }

    char currentPassword[MASTER_PASSWORD_LENGTH];
    printf("Unesite trenutnu master sifru: ");
    scanf("%s", currentPassword);

    if (!validateMasterPassword(currentPassword)) {
        printf("Trenutna master sifra nije tocna. Promjena sifre nije moguca.\n");
        return;
    }

    char newPassword[MASTER_PASSWORD_LENGTH];
    char confirmPassword[MASTER_PASSWORD_LENGTH];

    while (1) {
        printf("Unesite novu master sifru: ");
        scanf("%s", newPassword);

        if (strcmp(currentPassword, newPassword) == 0) {
            printf("Nova sifra mora biti razlicita od trenutne sifre. Molimo unesite ponovno.\n");
            continue;
        }

        if (!validatePassword(newPassword)) {
            printf("Nova sifra ne zadovoljava uvjete (malo, veliko slovo, broj, znak). Molimo unesite ponovno.\n");
            continue;
        }

        printf("Potvrdite novu master sifru: ");
        scanf("%s", confirmPassword);

        if (strcmp(newPassword, confirmPassword) != 0) {
            printf("Sifre se ne podudaraju. Molimo unesite ponovno.\n");
            continue;
        }


        setMasterPassword(newPassword);
        printf("Master sifra uspjesno promijenjena.\n");
        break;
    }
}
void deletePassword(const char* username) {
    FILE* file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Nije moguce otvoriti datoteku za citanje.\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Nije moguce otvoriti privremenu datoteku za pisanje.\n");
        fclose(file);
        return;
    }

    PASSWORD password;
    int found = 0;

    while (fscanf(file, "%s %s", password.username, password.password) == 2) {
        if (strcmp(password.username, username) == 0) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%s %s\n", password.username, password.password);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Lozinka s korisnickim imenom '%s' nije pronadena.\n", username);
        remove("temp.txt");
    }
    else {
        remove("passwords.txt");
        rename("temp.txt", "passwords.txt");
        printf("Lozinka uspjesno obrisana.\n");
    }
}
int validatePassword(const char* password) {
    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigit = 0;
    int hasSpecialChar = 0;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i]))
            hasUppercase = 1;
        else if (islower(password[i]))
            hasLowercase = 1;
        else if (isdigit(password[i]))
            hasDigit = 1;
        else
            hasSpecialChar = 1;
    }

    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int comparePasswords(const void* a, const void* b) {
    const PASSWORD* passwordA = (const PASSWORD*)a;
    const PASSWORD* passwordB = (const PASSWORD*)b;
    return strcmp(passwordA->username, passwordB->username);
}
