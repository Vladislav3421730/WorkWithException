#include <iostream>
#include<string>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include<limits>
using namespace std;

class Exception {
public:
	Exception() { cout << "Сработал конструктор класса Exception" << endl; }
	~Exception() { cout << "Сработал деструктор класса Exception" << endl; }
};
class AmountLessThanNullException : Exception {
public:
	AmountLessThanNullException() { cout << "Сработал конструктор класса  AmountLessThanNullException" << endl; }
	~AmountLessThanNullException() { cout << "Сработал деструктор класса  AmountLessThanNullException" << endl; }
};
class EmptyVectorException {};
class NotNumberException {
public:
	void what() {
		cout << "В данном случае надо вводить число" << endl;
	}
};



class JewelryShop {
private:
	string StoreName;
	string adress;
public:
	JewelryShop() : StoreName("Ювелирный парад"), adress("ул. Кедышко 10а") {}
	JewelryShop(string StoreName, string adress) {
		this->adress = adress;
		this->StoreName = StoreName;
	}

	void SetStoreName(string StoreName) {
		this->StoreName = StoreName;
	}

	void SetAdress(string adress) {
		this->adress = adress;
	}

	string GetStoreName() {
		return StoreName;
	}

	string GetAdress() {
		return adress;
	}

};

class Product {
private:
	string Name;
	int Amount;
	int coast;
public:
	Product() : Name("Кольцо"), Amount(15), coast(95) {}
	Product(string Name, int Amount, int coast) {
		this->Amount = Amount;
		this->coast = coast;
		this->Name = Name;
	}
	string getName() {
		return Name;
	}

	int getAmount() {
		return Amount;
	}

	int getCoast() {
		return coast;
	}

	void setName(string Name) {
		this->Name = Name;
	}

	void setAmount(int Amount) {
		this->Amount = Amount;
	}

	void setCoast(int coast) {
		this->coast = coast;
	}

};

class ProductsForOrders : public Product {

public:
	ProductsForOrders() : Product() {}
	ProductsForOrders(string Name, int Amount, int coast) : Product(Name, Amount, coast) {
		if (Amount <= 0) throw AmountLessThanNullException();
	}
};

class Customer {
private:
	string FIO;
	int CoastOfShoping;
public:
	Customer() : FIO("Панасик Владислав Вадимович"), CoastOfShoping(200) {}
	Customer(string FIO, int CoastOfShopping) {
		this->FIO = FIO;
		this->CoastOfShoping = CoastOfShopping;
	}

	void SetFIO(string FIO) {
		this->FIO = FIO;
	}

	void SetCoastOfShopping(int CoastOfShopping) {
		this->CoastOfShoping = CoastOfShopping;
	}

	string GetFIO() {
		return FIO;
	}

	int GetCoast() {
		return CoastOfShoping;
	}
};


class Order : public JewelryShop {
private:
	vector<ProductsForOrders> products;
	string DateOfOrder;
	string Number;
public:
	Order() {}
	Order(vector<ProductsForOrders>& products, string Number) {
		this->products = products;
		this->Number = Number;
	}
	Order(string Number) : Number(Number) {}

	vector<ProductsForOrders> getProducts() {
		return products;
	}

	string getDateOfOrder() {
		return DateOfOrder;
	}


	void setProducts(vector<ProductsForOrders>& products) {
		this->products = products;
	}

	void setDateOfOrder() {

		int day, month, hour, minuts;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		struct tm localtime;
		time_t now = time(NULL);
		localtime_s(&localtime, &now);
		day = localtime.tm_mday;
		month = 1 + localtime.tm_mon;
		hour = localtime.tm_hour;
		minuts = localtime.tm_min;

		string strDay = std::to_string(day);
		string strMonth = std::to_string(month);
		string strHour = std::to_string(hour);
		string strMinutes = std::to_string(minuts);

		this->DateOfOrder = strDay + "/" + strMonth + " " + strHour + ":" + strMinutes;

	}

	void setNumber(string number) {
		Number = number;
	}

	void addProduct(ProductsForOrders product) {
		products.push_back(product);
		cout << "Новое ювелирное украшение " << product.getName() << " было добавлено в заказ" << endl;
	}

	string GetNumber() {
		return Number;
	}

	void ShowOrder() {
		cout << "Заказ в магазине " << GetStoreName() << ", адресс " << GetAdress() << " под номером " << GetNumber() << endl;
		cout << "____________________________________________________" << endl;
		cout << "|  Название украшения | Количество | Цена за n штук|" << endl;
		cout << "|_____________________|____________|_______________|" << endl;
		int sum = 0;
		for (auto product : products) {
			cout << "|  " << setw(16) << product.getName() << "   |      " << setw(4) << product.getAmount() << "  |     "
				<< setw(8) << product.getCoast() << "  |" << endl;
			cout << "|_____________________|____________|_______________|" << endl;
			sum += product.getCoast();
		}
		setDateOfOrder();
		cout << "|   Сумма покупки     |          " << setw(6) << sum << "            |" << endl;
		cout << "|_____________________|____________________________|" << endl;
		cout << "|    Время заказа     |      " << setw(15) << DateOfOrder << "       |" << endl;
		cout << "|_____________________|____________________________|" << endl;
	}


};

void term_func() {
	cout << " Обработка исключения при помощи  метода terminate()" << endl;
}



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 0;
	set_terminate(term_func);

	JewelryShop jewerlyshop;
	Customer customer;
	Product product1("Серьги", 50, 20);
	Product product2("Кольцо", 80, 30);
	Product product3("Цепочка", 90, 12);
	Product product4("Бусы", 50, 50);
	Product product5("Браслеты", 90, 70);
	vector<Product> AvailibleProducts;
	vector<Order> orders;

	AvailibleProducts.push_back(product1);
	AvailibleProducts.push_back(product2);
	AvailibleProducts.push_back(product3);
	AvailibleProducts.push_back(product4);
	AvailibleProducts.push_back(product5);


	cout << "Добро пожаловать в ювелирный магазин" << endl;
	while (choice != 3) {
		cout << "1. Сделать заказ" << endl;
		cout << "2. Вывести все заказы" << endl;
		cout << "3. выйти из программы" << endl;
		try {
			cin >> choice;
			if (cin.fail())
			{

				cin.clear();
				cin.ignore(256, '\n');
				throw runtime_error("Нужно ввести число");

			}
		}
		catch (runtime_error e) {
			cout << e.what()<<endl;
			continue;
		}
		switch (choice) {
		case 1:
		{
			Order order;
			string number;
			cout << "Введите номер заказа" << endl;
			cin >> number;
			order.setNumber(number);
			cout << "Список доступных украшений :" << endl;
			for (auto product : AvailibleProducts) {
				cout << product.getName() << "  ";
			}
			string Name;
			int Amount;
			while (1) {
				string ch;
				cout << "\nХотите добавить  товар в заказ ? (y/n)" << endl;
				try {
					cin >> ch;
					if (ch.find_first_of("0123456789") != string::npos) throw "Когда в данном слкчае вводис цифры сработает метол terminate()";
					if (ch != "y" && ch != "n")
						throw 1;

				}
				catch (int) {
					cout << "Неправильно введёно номер операции" << endl;

				}
				if (ch == "n") break;
				else if (ch == "y") {
					cout << "\nВведите название товара : ";
					cin >> Name;
					try {
						bool result = false;
						for (auto product : AvailibleProducts) {
							if (product.getName() == Name) result = true;
						}
						if (!result) throw "Нет такого товара";
					}
					catch (const char*) {
						cout << "Нет такого товара" << endl;
						continue;
					}
					try {
						cout << "Введите количесвто товара : ";
						cin >> Amount;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(256, '\n');
							throw NotNumberException();
						}
						for (int i = 0; i < AvailibleProducts.size(); i++) {
							if (AvailibleProducts[i].getName() == Name) {
								if (Amount < AvailibleProducts[i].getAmount())
									AvailibleProducts[i].setAmount(AvailibleProducts[i].getAmount() - Amount);
								else throw 1;
							}
						}
					}
					catch (int) {
						cout << "Нет такого количества товара" << endl;
						continue;
					}
					catch (NotNumberException e) {
						e.what();
					}
					try {
						for (int i = 0; i < AvailibleProducts.size(); i++) {
							if (AvailibleProducts[i].getName() == Name) {
								if (customer.GetCoast() > AvailibleProducts[i].getCoast() * Amount) {
									int coast = AvailibleProducts[i].getCoast() * Amount;
									ProductsForOrders* productForOrder = new ProductsForOrders(Name, Amount, coast);
									customer.SetCoastOfShopping(customer.GetCoast() - coast);
									order.addProduct(*productForOrder);
								}
								else throw 1;
							}
						}
					}
					catch (int) {
						cout << " У покупателя нет денег на данный товар" << endl;
						continue;
					}
					catch (AmountLessThanNullException) {
						cout << "Отрицательное или нулевое количество товара невозможно " << endl;
					}
					catch (bad_alloc exc) {
						cout << "Возникло исключение " << exc.what() << endl;
					}
				}
			}
			try {
				if (order.getProducts().empty())
					throw EmptyVectorException();
				orders.push_back(order);
				cout << "Заказ под номером " << order.GetNumber() << " был оформлен" << endl;
			}
			catch (EmptyVectorException) {
				cout << "Вы не ввели ни одной единицы товара, оформление заказа под номером " << order.GetNumber() << " отменено" << endl;
			}
			break;
		}
		case 2:
		{
			try {
				if (orders.empty()) throw EmptyVectorException();
				cout << " Заказы " << customer.GetFIO() << endl;
				for (auto order : orders) {
					order.ShowOrder();
					cout << endl;
				}

			}
			catch (EmptyVectorException) {
				cout << "Нет заказов" << endl;
			}
			break;
		}
		case 3:return 0;
		}
	
	}

}
