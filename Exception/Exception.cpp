#include <iostream>
#include<string>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include<limits>
using namespace std;

class Exception {
public:
	Exception() { cout << "�������� ����������� ������ Exception" << endl; }
	~Exception() { cout << "�������� ���������� ������ Exception" << endl; }
};
class AmountLessThanNullException : Exception {
public:
	AmountLessThanNullException() { cout << "�������� ����������� ������  AmountLessThanNullException" << endl; }
	~AmountLessThanNullException() { cout << "�������� ���������� ������  AmountLessThanNullException" << endl; }
};
class EmptyVectorException {};
class NotNumberException {
public:
	void what() {
		cout << "� ������ ������ ���� ������� �����" << endl;
	}
};



class JewelryShop {
private:
	string StoreName;
	string adress;
public:
	JewelryShop() : StoreName("��������� �����"), adress("��. ������� 10�") {}
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
	Product() : Name("������"), Amount(15), coast(95) {}
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
	Customer() : FIO("������� ��������� ���������"), CoastOfShoping(200) {}
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
		cout << "����� ��������� ��������� " << product.getName() << " ���� ��������� � �����" << endl;
	}

	string GetNumber() {
		return Number;
	}

	void ShowOrder() {
		cout << "����� � �������� " << GetStoreName() << ", ������ " << GetAdress() << " ��� ������� " << GetNumber() << endl;
		cout << "____________________________________________________" << endl;
		cout << "|  �������� ��������� | ���������� | ���� �� n ����|" << endl;
		cout << "|_____________________|____________|_______________|" << endl;
		int sum = 0;
		for (auto product : products) {
			cout << "|  " << setw(16) << product.getName() << "   |      " << setw(4) << product.getAmount() << "  |     "
				<< setw(8) << product.getCoast() << "  |" << endl;
			cout << "|_____________________|____________|_______________|" << endl;
			sum += product.getCoast();
		}
		setDateOfOrder();
		cout << "|   ����� �������     |          " << setw(6) << sum << "            |" << endl;
		cout << "|_____________________|____________________________|" << endl;
		cout << "|    ����� ������     |      " << setw(15) << DateOfOrder << "       |" << endl;
		cout << "|_____________________|____________________________|" << endl;
	}


};

void term_func() {
	cout << " ��������� ���������� ��� ������  ������ terminate()" << endl;
}



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 0;
	set_terminate(term_func);

	JewelryShop jewerlyshop;
	Customer customer;
	Product product1("������", 50, 20);
	Product product2("������", 80, 30);
	Product product3("�������", 90, 12);
	Product product4("����", 50, 50);
	Product product5("��������", 90, 70);
	vector<Product> AvailibleProducts;
	vector<Order> orders;

	AvailibleProducts.push_back(product1);
	AvailibleProducts.push_back(product2);
	AvailibleProducts.push_back(product3);
	AvailibleProducts.push_back(product4);
	AvailibleProducts.push_back(product5);


	cout << "����� ���������� � ��������� �������" << endl;
	while (choice != 3) {
		cout << "1. ������� �����" << endl;
		cout << "2. ������� ��� ������" << endl;
		cout << "3. ����� �� ���������" << endl;
		try {
			cin >> choice;
			if (cin.fail())
			{

				cin.clear();
				cin.ignore(256, '\n');
				throw runtime_error("����� ������ �����");

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
			cout << "������� ����� ������" << endl;
			cin >> number;
			order.setNumber(number);
			cout << "������ ��������� ��������� :" << endl;
			for (auto product : AvailibleProducts) {
				cout << product.getName() << "  ";
			}
			string Name;
			int Amount;
			while (1) {
				string ch;
				cout << "\n������ ��������  ����� � ����� ? (y/n)" << endl;
				try {
					cin >> ch;
					if (ch.find_first_of("0123456789") != string::npos) throw "����� � ������ ������ ������ ����� ��������� ����� terminate()";
					if (ch != "y" && ch != "n")
						throw 1;

				}
				catch (int) {
					cout << "����������� ������ ����� ��������" << endl;

				}
				if (ch == "n") break;
				else if (ch == "y") {
					cout << "\n������� �������� ������ : ";
					cin >> Name;
					try {
						bool result = false;
						for (auto product : AvailibleProducts) {
							if (product.getName() == Name) result = true;
						}
						if (!result) throw "��� ������ ������";
					}
					catch (const char*) {
						cout << "��� ������ ������" << endl;
						continue;
					}
					try {
						cout << "������� ���������� ������ : ";
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
						cout << "��� ������ ���������� ������" << endl;
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
						cout << " � ���������� ��� ����� �� ������ �����" << endl;
						continue;
					}
					catch (AmountLessThanNullException) {
						cout << "������������� ��� ������� ���������� ������ ���������� " << endl;
					}
					catch (bad_alloc exc) {
						cout << "�������� ���������� " << exc.what() << endl;
					}
				}
			}
			try {
				if (order.getProducts().empty())
					throw EmptyVectorException();
				orders.push_back(order);
				cout << "����� ��� ������� " << order.GetNumber() << " ��� ��������" << endl;
			}
			catch (EmptyVectorException) {
				cout << "�� �� ����� �� ����� ������� ������, ���������� ������ ��� ������� " << order.GetNumber() << " ��������" << endl;
			}
			break;
		}
		case 2:
		{
			try {
				if (orders.empty()) throw EmptyVectorException();
				cout << " ������ " << customer.GetFIO() << endl;
				for (auto order : orders) {
					order.ShowOrder();
					cout << endl;
				}

			}
			catch (EmptyVectorException) {
				cout << "��� �������" << endl;
			}
			break;
		}
		case 3:return 0;
		}
	
	}

}
