#ifndef SICT_PERISHABLE_H
#define SICT_PERISHABLE_H
#include "NonPerishable.h"
#include "Date.h"
#include "Product.h"
#include "ErrorMessage.h"

namespace sict {
	class Perishable : public NonPerishable {
	private:
		Date expiryDate;

	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
	};
}
#endif