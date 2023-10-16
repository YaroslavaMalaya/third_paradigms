#include <cstring>
#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif


extern "C"
{
    EXPORT char* encrypt(char* rawText, int key) {
    int length = strlen(rawText);
    char* encryptedText = (char*)malloc(length + 1);

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

    EXPORT char* decrypt(char* encryptedText, int key) {
    int length = strlen(encryptedText);
    char* decryptedText = (char*)malloc(length + 1);

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
}

