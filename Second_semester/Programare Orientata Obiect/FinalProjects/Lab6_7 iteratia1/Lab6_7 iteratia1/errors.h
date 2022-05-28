#pragma once
#include <string>

using namespace std;

class POSError {
private:
    string message;
public:
    POSError(string message) : message(message) {}

    const string& getMessage() const;

};

class ValidationError : public POSError {
public:
    ValidationError(string message) :
        POSError(message) {}
};

class RangeError : public POSError {
public:
    RangeError(string message) : POSError(message) {}
};