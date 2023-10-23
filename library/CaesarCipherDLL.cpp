#include <cstring>
#include <cstdlib>
#include <cctype>

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
            if (isupper(ch)) {
                encryptedText[i] = (ch - 65 + key) % 26 + 65; // 65 = 'A'
            }
            else if (islower(ch)) {
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
        if (key > 26)
            key = key % 26;
        int length = strlen(encryptedText);
        char* decryptedText = (char*)malloc(length + 1);

        for (int i = 0; i < length; i++) {
            char ch = encryptedText[i];
            if (isupper(ch)) {
                decryptedText[i] = (ch - 65 - key + 26) % 26 + 65;
            }
            else if (islower(ch)) {
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

