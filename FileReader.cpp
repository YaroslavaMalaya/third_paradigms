#include "FileReader.h"
#include <fstream>
using namespace std;

const size_t chunk_size = 128;

string FileReader::read(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("File not found: " + filePath);
    }

    // get the size of the file
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg(); // the current position of the file pointer = file size
    file.seekg(0, ios::beg);

    string content;
    content.reserve(fileSize);
    vector<char> buffer(chunk_size);
    while (fileSize > 0) {
        size_t chunkSize = min(chunk_size, fileSize);
        file.read(buffer.data(), chunkSize);
        content.append(buffer.begin(), buffer.begin() + chunkSize);
        fileSize -= chunkSize;
    }
    return content;
}
