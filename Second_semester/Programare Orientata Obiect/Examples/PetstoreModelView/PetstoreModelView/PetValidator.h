#pragma once
#include "pet.h"
#include <string>
class PetValidator {
public:
	void validate(const Pet& p) {
		auto nonEmptyS = p.getSpecies().length() > 0;
		auto nonEmptyT = p.getType().length() > 0;
		auto nonNegP = p.getPrice()> 0;
		if (nonEmptyS && nonEmptyT && nonNegP) {
			return;//pet ok
		}
		std::string errMsg = "Invalid Pet (";
		if (!nonEmptyS) {
			errMsg += "species empty!,";
		}
		if (!nonEmptyT) {
			errMsg += "type empty!,";
		}
		if (!nonNegP) {
			errMsg += "price negativ!";
		}
		errMsg += ")";
		throw PetException(errMsg);
	}
};