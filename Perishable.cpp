#include <iostream>
#include "Perishable.h"
#include "ErrorMessage.h"
#include "Date.h"


using namespace std;
namespace sict {
	
	

	Perishable::Perishable() : NonPerishable('P') {
	}


	std::fstream& Perishable::store(std::fstream& file, bool NewLine) const {
		NonPerishable::store(file, false);
		file << "," << expiryDate;
		if (NewLine) {
			file << std::endl;
		}
		return file;
	}


	std::fstream& Perishable::load(std::fstream& file) {
		NonPerishable::load(file);
		file >> expiryDate;
		return file;
	}


	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		NonPerishable::write(os, linear);
		if (isClear()) {
			if (linear) {
				expiryDate.write(os);
			}
			else {
				os << "Expiry date: " << expiryDate;
			}
		}
		return os;
	}


	std::istream& Perishable::read(std::istream& is) {
		NonPerishable::read(is);
		if (isClear()) {
			cout << "Expiry date (YYYY/MM/DD): ";
			Date date;
			date.Date::read(is);

			if (date.errCode() == NO_ERROR) {
				expiryDate = date;
			}
			else {
				switch (date.errCode()) {
				case CIN_FAILED:
					message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					message("Invalid Day in Date Entry");
					break;
				}
				is.setstate(ios::failbit);
			}
		}
		return is;
	}

}