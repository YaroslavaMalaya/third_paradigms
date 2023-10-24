#include "FileWriter.h"
#include <fstream>
using namespace std;

const size_t chunk_size = 128;

void FileWriter::write(const string& filePath, const string& content) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing: " + filePath);
    }

    for(size_t i = 0; i < content.size(); i += chunk_size) {
        size_t chunkSize = min(chunk_size, content.size() - i);
        file.write(content.data() + i, chunkSize);
        // s - pointer to the position in the string from which the current chunk begins
    }
}