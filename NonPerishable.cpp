#include <iostream>
#include <cstring>
#include<fstream>
#include <iomanip>
#include "Product.h"
#include "NonPerishable.h"


using namespace std;
namespace sict {

	void NonPerishable::safe(){
	
		m_SkuOfPrduct[0] = '\0';
		m_PrductName = nullptr;
		m_PrductUnit[0] = '\0';
		m_QtyOnHand = 0;
		m_QtyRqrd = 0;
		m_PriceBfrTax = 0;
		ErrorMessage error;
	
	}
	NonPerishable::NonPerishable() {
		m_TypOfPrduct = 'N';
		safe();//removed code duplication here
	}

	NonPerishable::NonPerishable(char prductType) {
		m_TypOfPrduct = prductType;
		safe();//removed code duplication here
	}
	//7 arguments
	NonPerishable::NonPerishable(const char* SkuPrduct, const char* PrductName, const char *PrductUnit, int QtyOnHand, bool ChkTax, double BfrTax, int QtyRqrd) {
		strcpy(m_SkuOfPrduct, SkuPrduct);
		m_PrductName = new char[strlen(PrductName) + 1];
		strcpy(m_PrductName, PrductName);
		strcpy(m_PrductUnit, PrductUnit);
		m_QtyOnHand = QtyOnHand;
		m_chktax = ChkTax;
		m_PriceBfrTax = BfrTax;
		m_QtyRqrd = QtyRqrd;
		ErrorMessage error;
	}
	//copy 
	NonPerishable::NonPerishable(const NonPerishable& obj) {
		*this = obj;
	}
	//copy assignment
	NonPerishable& NonPerishable::operator = (const NonPerishable& nonP) {
		if (this != &nonP) {
			m_PrductName = new char[strlen(nonP.m_PrductName) + 1];
			strcpy(m_PrductName, nonP.m_PrductName);
			strcpy(m_SkuOfPrduct, nonP.m_SkuOfPrduct);
			strcpy(m_PrductUnit, nonP.m_PrductUnit);
			m_QtyOnHand = nonP.m_QtyOnHand;
			m_chktax = nonP.m_chktax;
			m_PriceBfrTax = nonP.m_PriceBfrTax;
			m_QtyRqrd = nonP.m_QtyRqrd;
		}
		else {

			delete[] m_PrductName;
			m_PrductName = nullptr;
		}
		return *this;
	}
	//destructor or resource releaser
	NonPerishable::~NonPerishable() {
		delete[]m_PrductName;
		m_PrductName = nullptr;
	}

	void NonPerishable::name(const char* PrductName) {
		if (PrductName != nullptr) {
			int len = strlen(PrductName);
			m_PrductName = new char[len + 1];
			strcpy(m_PrductName, PrductName);
		}
		else {
			delete[] m_PrductName;
			m_PrductName = nullptr;
		}
	}
	
	void NonPerishable::CopySku(const char * sku)
	{
		strcpy(m_SkuOfPrduct, sku);
	}
	void NonPerishable::CopyUnit(const char *unit) {
		strcpy(m_PrductUnit, unit);
	}
	void NonPerishable::CopyQRequired(const int qtyR) {
		m_QtyRqrd = qtyR;
	}
	void NonPerishable::CopyTaxes(const bool tax) {
		m_chktax = tax;
	}
	void NonPerishable::CopyPrice(const double price) {
		m_PriceBfrTax = price;
	}
	



	const char* NonPerishable::name() const {
		return m_PrductName == nullptr ? nullptr : m_PrductName;
	}

	double NonPerishable::cost() const {
		return m_chktax ? ((TaxRate + 1)*m_PriceBfrTax) : m_PriceBfrTax;
	}
	void NonPerishable::message(const char* errorMessage) {
		error.message(errorMessage);
	}
	bool NonPerishable::isClear() const {
		return error.isClear();
	}

	



	
	std::fstream& NonPerishable::store(std::fstream& file, bool newLine) const {
		if (file.is_open()) {
			file << this->m_TypOfPrduct << ','<< this->m_SkuOfPrduct << ','<< this->m_PrductName << ','<< this->m_PriceBfrTax << ','
				<< this->m_chktax << ','<< this->m_QtyOnHand << ','<< this->m_PrductUnit << ','<< this->m_QtyRqrd;

		}
		if (newLine) {
			file << endl;
		}
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file) {
		char Sku[MaxSkuLen];
		char Name[MaxNameLen];
		char Unit[MaxUnitLen];
		int Qty;
		int QtyRqrd;
		bool Tax;
		double PriceBfrTax;

		if (file.is_open()) {
			file.getline(Sku, MaxSkuLen + 1, ',');
			file.getline(Name, MaxNameLen, ',');
			file >> PriceBfrTax;
			file.ignore();
			file >> Tax;
			file.ignore();
			file >> Qty;
			file.ignore();
			file.getline(Unit, MaxUnitLen, ',');
			file >> QtyRqrd;
			file.ignore();

			CopySku(Sku);
			name(Name);
			CopyPrice(PriceBfrTax);
			quantity(Qty);
			CopyQRequired(QtyRqrd);
			CopyUnit(Unit);
			CopyTaxes(Tax);
		}
		return file;
	}


	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const {
		if (!error.isClear()) {
			os << error.message();
		}
		else {
			if (linear) {
				os << setw(MaxSkuLen) << left << setfill(' ') << m_SkuOfPrduct << '|'
					<< setw(20) << left << setfill(' ') << m_PrductName << '|'
					<< setw(7) << right << setfill(' ') << fixed << setprecision(2) << cost() << '|'
					<< setw(4) << right << setfill(' ') << m_QtyOnHand << '|'
					<< setw(10) << left << setfill(' ') << m_PrductUnit << '|'
					<< setw(4) << right << setfill(' ') << m_QtyRqrd << '|';
			}
			else {
				
					os << "Sku: " << m_SkuOfPrduct << endl;
					os << "Name: " << m_PrductName << endl;
					os << "Price: " << m_PriceBfrTax << endl;
					if (m_chktax) 
					os << "Price after tax: " << cost() << endl;
					else 
					os << "Price after tax: " << "N/A" << endl;
					os << "Quantity On Hand: " << m_QtyOnHand << " " << m_PrductUnit << endl;
					os << "Quantity Needed: " << m_QtyRqrd;
				}
			
			//removed code duplication here as you mentioned
				/*else {
					os << "Sku: " << m_SkuOfPrduct << endl;
					os << "Name: " << m_PrductName << endl;
					os << "Price: " << m_PriceBfrTax << endl;
					
					os << "Quantity On Hand: " << m_QtyOnHand << " " << m_PrductUnit << endl;
					os << "Quantity Needed: " << m_QtyRqrd << endl;
				}*/
			}

		return os;
	}


	std::istream& NonPerishable::read(std::istream& is) {

		this->message(nullptr);
		char Sku[MaxSkuLen];
		char Name[MaxNameLen];
		char Unit[MaxUnitLen];
		char Tax;
		double PriceBfrTax;
		int Qty;
		int QtyRqrd;
		bool ChkTax;

		if (error.isClear()) {

			cout << " Sku: ";
			is >> Sku;
			cout << " Name: ";
			is >> Name;
			cout << " Unit: ";
			is >> Unit;

			if (!is.fail()) {
				cout << " Taxed? (y/n): ";
				is >> Tax;
				if (Tax == 'Y' || Tax == 'y') {
					ChkTax = true;

				}
				else if (Tax == 'N' || Tax == 'n') {
					ChkTax = false;

				}
				else {
					is.istream::setstate(std::ios::failbit);
					error.message("Only (Y)es or (N)o are acceptable");

				}
			}

			if (!is.fail()) {
				cout << " Price: ";
				is >> PriceBfrTax;
				if (is.fail()) {
					error.message("Invalid Price Entry");
				}
			}


			if (!is.fail()) {
				cout << "Quantity On hand: ";
				is >> Qty;
				if (is.fail()) {
					error.message("Invalid Quantity Entry");
				}
			}

			if (!is.fail()) {
				cout << "Quantity Needed: ";
				is >> QtyRqrd;
				if (is.fail()) {
					error.message("Invalid Quantity Needed Entry");
				}
			}


			if (!is.fail()) {
				CopySku(Sku);
				name(Name);
				CopyPrice(PriceBfrTax);
				quantity(Qty);
				CopyQRequired(QtyRqrd);
				CopyUnit(Unit);
				CopyTaxes(ChkTax);
			}


		}
		return is;
	}

	//queries
	bool NonPerishable::operator==(const char* sku) const {
		return strcmp(m_SkuOfPrduct, sku) == 0;
	}

	double NonPerishable::total_cost() const {
		return cost() *m_QtyOnHand;
	}

	void NonPerishable::quantity(int qty) {
		m_QtyOnHand = qty;
	}

	bool NonPerishable::isEmpty() const {
		return m_PrductName == nullptr;
	}

	int NonPerishable::qtyNeeded() const {
		return m_QtyRqrd;
	}

	int NonPerishable::quantity() const {
		return m_QtyOnHand;
	}

	bool NonPerishable::operator>(const char* sku) const {
		return strcmp(m_SkuOfPrduct, sku) > 0;
	}

	int NonPerishable::operator+=(int qty) {
		if (qty > 0) {
			return m_QtyOnHand += qty;
		}
		return m_QtyOnHand;
	}

	bool NonPerishable::operator>(const Product& obj) const {
		return strcmp(m_PrductName, name()) > 0;
	}
	
	double operator+=(double& cost, const Product& obj) {
		cost += obj.total_cost();
		return cost;
	}

	std::ostream& operator<<(std::ostream& os, const Product& obj) {
		obj.write(os, true);
		return os;
	}


	std::istream& operator>>(std::istream& is, Product&obj) {
		obj.read(is);
		return is;
	}

	
	Product* CreateProduct() {
		Product* product = nullptr;
		product = new NonPerishable('\0');
		return product;
	}
}
