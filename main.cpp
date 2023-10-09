#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

char* encrypt(char* rawText, int key) {
    int length = strlen(rawText);
    char* encryptedText = (char*) malloc(length + 1);

    for (int i = 0; i < length; i++) {
        char ch = rawText[i];
        if (ch >= 'A' && ch <= 'Z') {
            encryptedText[i] = (ch - 65 + key) % 26 + 65; // 65 = 'A'
        }
        else if (ch >= 'a' && ch <= 'z') {
            encryptedText[i] = (ch - 97 + key) % 26 + 97; // 97 = 'a'
        }
        else {
            encryptedText[i] = ch;
        }
    }

    encryptedText[length] = '\0';

    return encryptedText;
}

char* decrypt(char* encryptedText, int key) {
    int length = strlen(encryptedText);
    char* decryptedText = (char*) malloc(length + 1);

    for (int i = 0; i < length; i++) {
        char ch = encryptedText[i];

        if (ch >= 'A' && ch <= 'Z') {
            decryptedText[i] = (ch - 65 - key + 26) % 26 + 65;
        }
        else if (ch >= 'a' && ch <= 'z') {
            decryptedText[i] = (ch - 97 - key + 26) % 26 + 97;
        }
        else {
            decryptedText[i] = ch;
        }
    }

    decryptedText[length] = '\0';

    return decryptedText;
}


int main() {
    int key = 0;
    char input[10000];

    while (true){
        cout << "\n\nEnter text (please no more than 10000 symbols): ";
        cin.getline(input, sizeof(input));
        cout << "Enter number-key: ";
        cin >> key;
        cin.ignore();

        char* encryptedMessage = encrypt(input, key);
        char* decryptedMessage = decrypt(encryptedMessage, key);
        printf("Encrypted Message: %s", encryptedMessage);
        printf("\nDecrypted Message: %s", decryptedMessage);

        free(decryptedMessage);
        free(encryptedMessage);
    }
}