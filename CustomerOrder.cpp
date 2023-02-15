

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
namespace sdds {
	CustomerOrder::CustomerOrder() {}
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(std::string str) {
		bool extracted = false;
		size_t currPos = 0, i = 0;
		Utilities util_obj;
		m_name = util_obj.extractToken(str, currPos, extracted);
		if (extracted)
			m_product = util_obj.extractToken(str, currPos, extracted);
		if (m_widthField < util_obj.getFieldWidth())
			m_widthField = util_obj.getFieldWidth();
		m_cntItem = count(str.begin(), str.end(), util_obj.getDelimiter()) - 1;
		std::vector<Item*> items;
		while (extracted) {
			items.push_back(new Item(util_obj.extractToken(str, currPos, extracted)));
		}
		m_lstItem = new Item * [m_cntItem];
		std::for_each(items.begin(), items.end(), [&](Item* items_i) {
			m_lstItem[i] = items_i;
			i++; });
	}
	CustomerOrder::CustomerOrder(CustomerOrder& obj) {
		throw "ERROR: Cannot make copies.";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept {
		*this = std::move(obj);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept {
		if (this != &obj) {
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
			this->m_name = obj.m_name;
			this->m_product = obj.m_product;
			this->m_lstItem = obj.m_lstItem;
			this->m_cntItem = obj.m_cntItem;
			obj.m_name = "";
			obj.m_product = "";
			obj.m_cntItem = 0;
			obj.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [](const Item* i) {
			return i->m_isFilled;
			});
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](Item* i) {
			bool res = true;
			if (i->m_itemName == itemName)
				res = i->m_isFilled;
			return res;
			});
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
			{
				if (station.getQuantity() > 0)
				{

					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					os.width(11);
					os.setf(std::ios::right);
					os << "Filled ";
					os.unsetf(std::ios::right);
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					return;
				}
				else
				{
					os.width(19);
					os.setf(std::ios::right);
					os << "Unable to fill ";
					os.unsetf(std::ios::right);
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}

	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item* item) {
			os << "[" << std::setw(6) << std::setfill('0') << item->m_serialNumber << "] " << std::left << std::setfill(' ') << std::setw(m_widthField) << item->m_itemName << std::right << " - ";
			if (item->m_isFilled)
				os << "FILLED";
			else
				os << "TO BE FILLED";
			os << std::endl;
			});

	}
}
