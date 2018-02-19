#ifndef SICT_DATE_H
#define SICT_DATE_H
#include <iostream>


namespace sict {

	#define NO_ERROR 0     
	#define CIN_FAILED 1   
	#define YEAR_ERROR 2   
	#define MON_ERROR 3   
	#define DAY_ERROR 4 
	
  	const int min_year = 2000;
	const int max_year = 2030;
	
class Date {
		
		int mdays(int, int)const;
		void errCode(int errorCode);
	
	private:
		int value()const;
		int m_Year; 
		int m_Month; 
		int m_Day; 
		int error_state;
	public:
		Date();
		Date(int year, int month, int day);
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;

	};

	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date& );


}
#endif
