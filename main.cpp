#include <iostream>
#include <cstdio>
#include <windows.h>
using namespace std;

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

int main() {
    HINSTANCE handle = LoadLibrary(TEXT("liblibrary.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        cout << "Lib not found" << endl;
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    if (encrypt_ptr == nullptr) {
        cout << "Encrypt function not found" << endl;
        return 1;
    }

    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");
    if (decrypt_ptr == nullptr) {
        cout << "Decrypt function not found" << endl;
        return 1;
    }

    int key = 0;
    char input[10000];

    while (true) {
        cout << "\n\nEnter text (please no more than 10000 symbols): ";
        cin.getline(input, sizeof(input));
        cout << "Enter number-key: ";
        cin >> key;
        cin.ignore();

        char* encryptedMessage = encrypt_ptr(input, key);
        char* decryptedMessage = decrypt_ptr(encryptedMessage, key);
        printf("Encrypted Message: %s", encryptedMessage);
        printf("\nDecrypted Message: %s", decryptedMessage);

        free(decryptedMessage);
        free(encryptedMessage);
    }

    FreeLibrary(handle);
    return 0;
}
