#include <iostream>
#include <cstdio>
#include <dlfcn.h>
#include "FileReader.h"
#include "FileWriter.h"
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
    int mode;
    string inputPath, outputPath;
    string operation;
    FileReader fileReader;
    FileWriter fileWriter;
    string content;
    char* result;

    while (true) {
        cout << "Choose mode (1 for Normal, 2 for Secret, 3 for Exit): ";
        cin >> mode;
        cin.ignore();

        if (mode == 1){
            cout << "Enter operation (encrypt/decrypt): ";
            cin >> operation;
            cout << "Enter number-key for encryption/: ";
            cin >> key;
            cin.ignore();
        }
        else if (mode == 2){
            operation = "encrypt";
            key = rand() % 26;
        }
        else if (mode == 3){
            break;
        }
        else{
            cout << "Invalid mode selected. Try again." << endl;
        }

        cout << "Enter input file path: ";
        cin >> inputPath;
        cout << "Enter output file path: ";
        cin >> outputPath;

        try {
            content = fileReader.read(inputPath);
        } catch (const runtime_error& e) {
            cout << "Error reading file: " << e.what() << endl;
            continue;
        }

        if (operation == "encrypt") {
            result = encrypt_ptr(const_cast<char*>(content.c_str()), key);
        } else if (operation == "decrypt") {
            result = decrypt_ptr(const_cast<char*>(content.c_str()), key);
        } else {
            cout << "Invalid operation. Please enter 'encrypt' or 'decrypt'." << endl;
            continue;
        }

        fileWriter.write(outputPath, result);
        free(result);
        result = NULL;
        cout << "Operation successful. Result written to " << outputPath << endl;
    }

    dlclose(handle);
    return 0;
}
