#ifndef SICT_NONPERISHABLE_H_
#define SICT_NONPERISHABLE_H_
#include <iostream>
#include <fstream>
#include "ErrorMessage.h"
#include "Product.h"


namespace sict {
		const int MaxSkuLen = 7;
		const int MaxUnitLen = 10;
		const int MaxNameLen = 75;
		const double TaxRate = 0.13;

	class NonPerishable : public Product {
	private:
		char m_TypOfPrduct;
		char m_SkuOfPrduct[MaxSkuLen + 1];
		char* m_PrductName;
		char m_PrductUnit[MaxUnitLen + 1];
		int m_QtyOnHand;
		int m_QtyRqrd;
		double m_PriceBfrTax;
		bool m_chktax;
		ErrorMessage error;

	protected:

		void name(const char*);  
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		NonPerishable();
		void safe();
		NonPerishable(char);
		NonPerishable(const char*, const char*, const char*, int QtyOnHand = 0, bool ChkTax = true, double BfrTax = 0, int QtyRqrd = 0);
		NonPerishable(const NonPerishable&);
		NonPerishable& operator=(const NonPerishable&);
		~NonPerishable();
		void CopySku(const char *);
		void CopyUnit(const char *);
		void CopyQRequired(const int qtyN);
		void CopyTaxes(const bool);
		void CopyPrice(const double);
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);  
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;

			};
	
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();

}
#endif