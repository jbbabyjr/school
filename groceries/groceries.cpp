#include "split.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>

using namespace std;
class Customer;
class Item;
class Order;

vector<Customer> customers;
vector<Item> items;
list<Order> orders;

class Customer {
public:
	Customer(vector<string> params) {
		cid = stoi(params.at(0));
		name = params.at(1);
		addy = params.at(2);
		city = params.at(3);
		state = params.at(4);
		zip = params.at(5);
		number = params.at(6);
		email = params.at(7);
	}
	string print_detail() {
		string details = "Customer ID #" + to_string(cid) + ":\n";
		details += name + ", ph. " + number + ", email: " + email + "\n";
		details += addy + "\n";
		details += city + ", " + state + " " + zip + "\n\n";
		return details;
	}
	int get_cid() {
		return cid;
	}
private: 
	int cid;
	string name;
	string addy;
	string city;
	string state;
	string zip;
	string number;
	string email;
};

int findCust(int id) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers.at(i).get_cid() == id) {
			return i;
		}
	}
	return -1;
}
// end customer

class Item {
public:
	Item(vector<string> params) {
		iid = stoi(params.at(0));
		desc = params.at(1);
		price = stod(params.at(2));
	}
	int get_iid() {
		return iid;
	}
	string get_desc() {
		return desc;
	}
	double get_price() {
		return price;
	}
private:
	int iid;
	string desc;
	double price;
};

int findItem(int id) {
	for (int i = 0; i < items.size(); i++) {
		if (items.at(i).get_iid() == id) {
			return i;
		}
	}
	return -1;
}

class LineItem {
public:
	LineItem(string item) {
		vector<string> details = split(item, '-');
		item_id = stoi(details.at(0));
		qty = stoi(details.at(1));
	}
	double sub_total() {
		cout << fixed << setprecision(2);
		return items.at(findItem(item_id)).get_price() * qty;
	}
	friend bool operator<(const LineItem& item1, const LineItem& item2) {
		return item1.item_id < item2.item_id;
	}
	int getid() {
		return item_id;
	}
	int getqty() {
		return qty;
	}
private:
	int item_id;
	int qty;
};

// end items

class Payment {
public:
	virtual string print_detail() const = 0;
private:
	friend class Order;
	double amount;
};

class Credit : public Payment {
public:
	Credit(vector<string> params) {
		card_number = params.at(1);
		expiration = params.at(2);
	}
	string print_detail() const override {
		return "Credit card " + card_number + ", exp. " + expiration;
	}
private:
	string card_number;
	string expiration;
};

class PayPal : public Payment {
public:
	PayPal(vector<string> params) {
		paypal_id = params.at(1);
	}
	string print_detail() const override {
		return "Paypal ID: " + paypal_id;
	}
private:
	string paypal_id;
};

class WireTransfer : public Payment {
public:
	WireTransfer(vector<string> params) {
		bank_id = params.at(1);
		account_id = params.at(2);
	}
	string print_detail() const override {
		return "Wire transfer from Bank ID " + bank_id + ", Account# " + account_id;
	}
private:
	string bank_id;
	string account_id;
};

//end of payment stuff

class Order {
	
public:
	Order(vector<string> params, vector<string> pay /*Payment* pay*/) {
		cust_id = stoi(params.at(0));
		order_id = stoi(params.at(1));
		order_date = params.at(2);
		for (int i = 3; i < params.size(); i++) {
			LineItem item(params.at(i));
			line_items.push_back(item);
		}
		sort(line_items.begin(), line_items.end());
		if (pay.at(0) == "1") {
			payment = new Credit(pay);
			payment->amount = total();
		}
		else if (pay.at(0) == "2") {
			payment = new PayPal(pay);
			payment->amount = total();
		}
		else if (pay.at(0) == "3") {
			payment = new WireTransfer(pay);
			payment->amount = total();
		}
	}
	~Order() {
		delete payment;
	}
	double total() {
		double price = 0.00;
		for (int i = 0; i < line_items.size(); i++) {
			price += line_items.at(i).sub_total();
		}
		return price;
	}
	string print_order() {
		ostringstream oOSS;
		oOSS << fixed << setprecision(2) << "===========================\n" 
			<< "Order #" << order_id << ", Date: " << order_date << "\n" 
			<< "Amount: $" << total() << ", Paid by " 
			<< payment->print_detail() << "\n\n"
			<< customers.at(findCust(cust_id)).print_detail() 
			<< "Order Detail: \n";
		for (int i = 0; i < line_items.size(); i++) {
			int id = findItem(line_items.at(i).getid());
			oOSS << "\tItem " << line_items.at(i).getid() << ": \"" << items.at(id).get_desc() << "\", " << line_items.at(i).getqty() << " @ " << items.at(id).get_price() << "\n";
		}
		string order = oOSS.str();
		return order;
	}
private:
	int order_id;
	string order_date;
	int cust_id;
	vector<LineItem> line_items;
	Payment* payment;
};

void read_customers(string f) { // WORKS (seemingly hahaha)
	ifstream inFS;
	string preCustomer;
	vector<string> splitCust;
	inFS.open(f);
	if (!inFS.is_open()) {
		cout << "Could not open file " << f << endl;
	}
	else {
		while (!inFS.eof()) {
			getline(inFS, preCustomer);
			if (!inFS.fail()) {
				splitCust = split(preCustomer, ',');
				if (splitCust.size() == 8) {
					Customer customer(splitCust);
					customers.push_back(customer);
				}
			}
			
		}
	}
	
	inFS.close();
}

void read_items(string f) { //WORKS (seemingly)
	ifstream inFS;
	string preItem;
	vector<string> splitItem;
	inFS.open(f);
	if (!inFS.is_open()) {
		cout << "Could not open file " << f << endl;
	}
	else {
		while (!inFS.eof()) {
			getline(inFS, preItem);
			if (!inFS.fail()) {
				splitItem = split(preItem, ',');
				if (splitItem.size() == 3) {
					Item item(splitItem);
					items.push_back(item);
				}
			}

		}
	}

	inFS.close();
}

void read_orders(string f) {
	ifstream inFS;
	string preOrder;
	string prePayment;
	vector<string> splitOrder;
	vector<string> splitPayment;
	
	inFS.open(f);
	if (!inFS.is_open()) {
		cout << "Could not open file " << f << endl;
	}
	else {
		while (!inFS.eof()) {
			getline(inFS, preOrder);
			getline(inFS, prePayment);
			if (!inFS.fail()) {
				splitOrder = split(preOrder, ',');
				splitPayment = split(prePayment, ',');
				orders.emplace_back(splitOrder, splitPayment);
			}
		}
	}
}

int main() {
	read_customers("customers.txt");
	read_items("items.txt");
	read_orders("orders.txt");
	
	ofstream ofs("order_report.txt");
	for (auto& order : orders)
		ofs << order.print_order() << endl;
}