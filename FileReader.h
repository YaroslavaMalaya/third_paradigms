#pragma once
#include <string>
using namespace std;

class IReader {
public:
    virtual ~IReader() = default;
    virtual string read(const string& filePath) = 0;
};

class FileReader : public IReader {
public:
    string read(const string& filePath) override;
};
