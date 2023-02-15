

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include"Utilities.h"

namespace sdds
{
	std::string& Trim(std::string& str)
	{
		str.erase(str.find_last_not_of(' ')+1);
		str.erase(0, str.find_first_not_of(' '));

		return str;
	}
	char Utilities::m_delimiter{};


	void Utilities::setFieldWidth(size_t newWidth){
		m_widthField = newWidth;
	}


	size_t Utilities::getFieldWidth() const{
		return m_widthField;
	}


	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
		std::string token{};
		size_t found = str.find(m_delimiter,next_pos);
		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw "Delimeter Found!!\n";
		}

		token = str.substr(next_pos, found-next_pos);

		if (found == std::string::npos)
		{
			more = false;
		}
		else {
			next_pos = found + 1;
			more = true;
		}

		if (m_widthField < token.length())
		{
			m_widthField = token.length();
		}

		return Trim(token);
	}


	void Utilities::setDelimiter(char newDelimiter){
		m_delimiter = newDelimiter;
	}


	char Utilities::getDelimiter(){
		return m_delimiter;
	}
	Utilities::~Utilities()
	{
	}


}



