#include <iostream>
#include <cstdio>
#include <dlfcn.h>
using namespace std;

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

int main() {
    void* handle = dlopen("./liblibrary.dylib", RTLD_LAZY);
    if (!handle) {
        cout << "Lib not found. Error: " << dlerror() << endl;
        return 1;
    }
    dlerror(); // clear any existing errors

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)dlsym(handle, "encrypt");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cout << "Encrypt function not found. Error: " << dlsym_error << endl;
        return 1;
    }

    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)dlsym(handle, "decrypt");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cout << "Decrypt function not found. Error: " << dlsym_error << endl;
        return 1;
    }

    int key = 0;
    char input[10000];

    while (true) {
        cout << "\n\nEnter text (please no more than 10000 symbols): ";
        cin.getline(input, sizeof(input));
        cout << "Enter number-key for encryption: ";
        cin >> key;
        cin.ignore();

        char* encryptedMessage = encrypt_ptr(input, key);
        cout << "Encrypted Message: " <<  encryptedMessage << endl;
        cout << "Enter number-key for decryption: ";
        cin >> key;
        cin.ignore();
        char* decryptedMessage = decrypt_ptr(encryptedMessage, key);
        cout << "Decrypted Message: " << decryptedMessage << endl;

        free(decryptedMessage);
        free(encryptedMessage);
    }

    dlclose(handle);
    return 0;
}
