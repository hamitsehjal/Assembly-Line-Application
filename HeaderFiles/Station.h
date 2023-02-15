

#pragma once
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds
{
	class Station {
		size_t m_StationId{};
		std::string m_itemName{};
		std::string m_stationDescription{};
		size_t m_nextSerialNumber{};
		size_t m_itemsIntStock{};
		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		~Station();
	};
}

#endif // !SDDS_STATION_H

