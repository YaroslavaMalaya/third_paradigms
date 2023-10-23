#pragma once
#include <string>
using namespace std;

class IWriter {
public:
    virtual ~IWriter() = default;
    virtual void write(const string& filePath, const string& content) = 0;
};

class FileWriter : public IWriter {
public:
    void write(const string& filePath, const string& content);
};