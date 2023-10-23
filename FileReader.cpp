#include "FileReader.h"
#include <fstream>
using namespace std;

string FileReader::read(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("File not found: " + filePath);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}
