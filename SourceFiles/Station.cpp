

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include"Station.h"
#include"Utilities.h"

namespace sdds
{
	size_t Station::m_widthField{ 0 };
	size_t Station::id_generator{ 0 };
	Station::Station(const std::string str){
		m_StationId = ++id_generator;
		Utilities item{};
		size_t start = 0;
		bool more{ false };
		m_itemName = item.extractToken(str,start,more);
		m_nextSerialNumber = std::stoi(item.extractToken(str, start, more)); 
		m_itemsIntStock = std::stoi(item.extractToken(str, start, more));

		Station::m_widthField = Station::m_widthField + item.getFieldWidth();
		m_stationDescription = item.extractToken(str, start, more);
	}
	const std::string& Station::getItemName() const{
		return m_itemName;
	}
	size_t Station::getNextSerialNumber(){
		return m_nextSerialNumber++;
	}
	size_t Station::getQuantity() const{
		return m_itemsIntStock;
	}
	void Station::updateQuantity(){
		if (getQuantity() > 0)
		{
			m_itemsIntStock--;
		}
	}
	void Station::display(std::ostream& os, bool full) const{
		if (!full)
		{
			// ID | NAME | SERIAL |
			os << std::setw(3) << std::setfill('0') << m_StationId << " | ";
			os << std::left<<std::setw(15) << std::setfill(' ') << m_itemName<<" | ";
			os << std::right<<std::setw(6) << std::setfill('0') << m_nextSerialNumber << " | " << std::endl;
		}
		else
		{
			//ID | NAME | SERIAL | QUANTITY | DESCRIPTION
			os << std::right<<std::setw(3) << std::setfill('0') << m_StationId << " | ";
			os << std::left<<std::setw(15) << std::setfill(' ') << m_itemName << " | ";
			os << std::right<<std::setw(6) << std::setfill('0') << m_nextSerialNumber << " | ";
			os << std::right<<std::setw(4) << std::setfill(' ') << m_itemsIntStock << " | ";
			os << m_stationDescription  << std::endl;
		}
	}
	Station::~Station()
	{

	}
}
