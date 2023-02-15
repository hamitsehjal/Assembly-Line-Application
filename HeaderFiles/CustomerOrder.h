

#ifndef SDDS_CUSTOMERORDER__
#define SDDS_CUSTOMERORDER__
#include <string>
#include "Station.h"
namespace sdds {
	struct Item
	{
		std::string m_itemName{};
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name;
		std::string m_product;
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;

		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(std::string str);
		CustomerOrder(CustomerOrder& obj);
		CustomerOrder(CustomerOrder&& obj) noexcept;
		CustomerOrder& operator=(CustomerOrder&& obj) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SDDS_CUSTOMERORDER__
