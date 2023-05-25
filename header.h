#ifndef HEADER_H
#define HEADER_H

void displaySubmenuViewPasswords();
void displaySubmenuAddPassword();
void displaySubmenuGeneratePassword();
void displaySubmenuEditPassword();
void displaySubmenuDeletePassword();
void displaySubmenuChangeMasterPassword();
void displaySubmenuHelp();
void displayInstructions();
void displayDescription();
void addPassword();


typedef struct {
    char name[100];
    char password[100];
} ACCOUNT;

typedef struct {
    char username[100];
    char password[100];
} PASSWORD;

#endif  //HEADER_H
