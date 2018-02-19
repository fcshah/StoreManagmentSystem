#include"ErrorMessage.h"

namespace sict {
	
	ErrorMessage::ErrorMessage(const char* errorMessage) {
		if (errorMessage != nullptr) {

			int length = strlen(errorMessage);
			m_errMsg = new char[length + 1];
			int i = 0;
			for (i = 0; i <= length; i++) {
				m_errMsg[i] = errorMessage[i];
			}
		}
		else
			m_errMsg = nullptr;
	}

	ErrorMessage::~ErrorMessage() {
		clear();
	}

	void ErrorMessage::clear() {
		if (m_errMsg != nullptr) {
			delete[] m_errMsg;
			m_errMsg = nullptr;
		}
	}

	bool ErrorMessage::isClear() const {
		return m_errMsg == nullptr;
	}

	void ErrorMessage::message(const char* str) {
		clear();
		if (str != nullptr) {
			m_errMsg = new char[strlen(str) + 1];
			strcpy(m_errMsg, str);
		}
	}

	const char* ErrorMessage::message()const {
		return m_errMsg;
	}

	std::ostream& operator<<(std::ostream& out, const ErrorMessage& error) {
		if (!error.isClear()) {
			return out << error.message();
		}
		return out;
	}
}