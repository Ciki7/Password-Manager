#ifndef HEADER_H
#define HEADER_H

#define MAX_PASSWORDS 100
#define FILENAME "passwords.txt"
#define MASTER_PASSWORD_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MASTER_PASSWORD_FILE "master_password.txt"


typedef struct {
    char username[100];
    char password[100];
} PASSWORD;


void displaySubmenuViewPasswords();
void displaySubmenuAddPassword();
void displaySubmenuEditPassword();
void displaySubmenuDeletePassword();
void displaySubmenuChangeMasterPassword();
void displaySubmenuHelp();
void displayInstructions();
void displayDescription();
void addPassword(PASSWORD passwords[], int* numPasswords);
void savePasswords(PASSWORD passwords[], int numPasswords);
void displayPasswords(PASSWORD passwords[], int numPasswords);
void editPassword(const char* filename);
void requestMasterPassword();
int isMasterPasswordSet();
void setMasterPassword(const char* password);
void changeMasterPassword();
void searchPasswords(const char* username);
void deletePassword(const char* username);
int validatePassword(const char* password);
int comparePasswords(const void* a, const void* b);

#endif  // HEADER_H
