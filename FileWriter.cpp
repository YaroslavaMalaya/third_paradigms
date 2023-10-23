#include "FileWriter.h"
#include <fstream>
using namespace std;

void FileWriter::write(const string& filePath, const string& content) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing: " + filePath);
    }
    file << content;
}