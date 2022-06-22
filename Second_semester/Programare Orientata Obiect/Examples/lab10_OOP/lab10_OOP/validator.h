#pragma once
#include <vector>
#include <string>
#include <ostream>
#include "Locatar.h"

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
	string getMsg() {
		string fullMsg = "";
		for (const string e : msgs) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class LocatarValidator {
public:
	void validate(const Locatar& l);
};
void testValidate();
