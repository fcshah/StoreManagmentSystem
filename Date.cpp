#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace std;
namespace sict {

	Date::Date() {
		m_Year = 0;
		m_Month = 0;
		m_Day = 0;
		error_state = NO_ERROR;
	}
	
	int Date::value()const {
		return m_Year * 372 + m_Month * 13 + m_Day;
	}

	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	
	void Date::errCode(int errorCode) {
		error_state = errorCode;
	}

	Date::Date(int year, int month, int day) {
		if (!((year <= max_year  && year>= min_year) && (month >= 1 && month <= 12) && (day >= 1 && day <= mdays(month, year)))) {
			
			*this = Date();
		}
		else {
			m_Year = year;
			m_Month = month;
			m_Day = day;
			error_state = NO_ERROR;
		}
	}

	
	bool Date::operator==(const Date& rhs) const {
		return this->value() == rhs.value();
	}

	bool Date::operator!=(const Date& rhs) const {
		return this->value() != rhs.value();
	}

	bool Date::operator<(const Date& rhs) const {
		return this->value() < rhs.value();
	}

	bool Date::operator>(const Date& rhs) const {
		return this->value() > rhs.value();
	}

	bool Date::operator<=(const Date& rhs) const {
		return this->value() <= rhs.value();
	}

	bool Date::operator>=(const Date& rhs) const {
		return this->value() >= rhs.value();
	}

	int Date::errCode() const {
		return error_state;
	}

	bool Date::bad() const {
		return error_state != 0;
	}

	std::istream& Date::read(std::istream& istr) {
		istr >> m_Year;
		istr.ignore();
		istr >> m_Month;
		istr.ignore();
		istr >> m_Day;

		if (!(istr.fail())) {
			if (!(min_year <= m_Year && m_Year <= max_year)) {
				error_state = YEAR_ERROR;
				Date::Date();//removed code duplication here
				/*m_Year = 0;
				m_Month = 0;
				m_Day = 0;*/
			}
			else if (m_Month < 1 && m_Month > 12) {
				error_state = MON_ERROR;
				Date::Date();//removed code duplication here
				/*m_Year = 0;
				m_Month = 0;
				m_Day = 0;*/

			}
			else if (!(1 <= m_Day && m_Day <= mdays(m_Month, m_Year))) {
				error_state = DAY_ERROR;
				Date::Date();//removed code duplication here
				/*m_Year = 0;
				m_Month = 0;
				m_Day = 0;*/
			}
			else {
				error_state = NO_ERROR;
			}

		}
		else {
			error_state = CIN_FAILED;
		}
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		if (!( m_Month > 10 && m_Day > 10)) {
			ostr << m_Year << "/" << setw(2) << setfill('0') << m_Month << "/" << setw(2) << setfill('0') << m_Day;
		}
		else if (10 > m_Month) {
			ostr << m_Year << "/" << setw(2) << setfill('0') << m_Month << "/" << m_Day;
		}
		else if (m_Day < 10) {
			ostr << m_Year << "/" << m_Month << "/" << setfill('0') << m_Day;
		}
		else {
			ostr << m_Year << "/" << m_Month << "/" << m_Day;
		}
		return ostr;


	}

	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		return date.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Date& date) {
		return date.read(istr);
	}


}
