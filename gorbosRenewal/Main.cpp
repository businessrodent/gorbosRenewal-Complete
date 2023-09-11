#include <iostream>
#include <vector>
#include <map>
using namespace std;

int i = 0;
int gold = 80;

struct Item {
	string name;
	int val;
	int nom;
	string desc;
	Item(string name, int val, int nom, string desc) {
		this->name = name;
		this->val = val;
		this->nom = nom;
		this->desc = desc;
	}
};

struct Inventory {
	vector<Item> list;

	void add(Item item) {
		bool y = 0;
		for (Item& x : list) {
			if (x.name == item.name) {
				y = 1;
				x.nom++;
				break;
			}
		};
		if (y == 0) {
			Item b = item;
			b.nom = 1;
			list.push_back(b);
		}
	};

	void sub(Item item) {
		bool y = 0;
		int n = 0;
		for (Item& x : list) {
			if (x.name == item.name) {
				if (x.nom > 1) {
					x.nom--;
				}
				else {
					list.erase(list.begin() + n);
				}
			}
			n++;
		};
	};

	Inventory(vector<Item> list) {
		this->list = list;
	}
	Inventory() {
	}
};

Inventory shop, inv;

void shopBuy() { // defines the interaction with the shop (buying)
	int i = 0;
	int inp;
	cout << "shop: \n";

	for (const Item& item : shop.list) {
		i++;
		cout << i << ". " << item.name << " x" << item.nom << " - price: " << item.val << "\n";
	}
	cout << shop.list.size() + 1 << ". back \n";

	while (1) {
		cin >> inp;
		if (cin.fail()) {
			//Not an int.
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (0 < inp && inp <= shop.list.size() + 1) {
			break;
		}
		cout << "invalid \n";
	}
	if (inp < shop.list.size()+1) {
		if (gold >= shop.list[inp - 1].val) {
			gold -= shop.list[inp - 1].val;
			inv.add(shop.list[inp - 1]);
			shop.sub(shop.list[inp - 1]);
		}
		else {
			cout << "not enough gold \n";
		}
	}
};

void shopSell() {
	int i = 0;
	int inp;
	cout << "inventory: \n";
	for (const Item& item : inv.list) {
		i++;
		cout << i << ". " << item.name << " x" << item.nom << " - price: " << item.val << "\n";
	}
	cout << inv.list.size() + 1 << ". back \n";
	while (1) {
		cin >> inp;
		if (cin.fail()) {
			//Not an int.
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (0 < inp && inp <= inv.list.size() + 1) {
			break;
		}
		cout << "invalid \n";
	}
	if (inp < inv.list.size() + 1) {
		if (inv.list[inp - 1].name == "gorbo's kidney" && inv.list[inp - 1].nom == 2) {
			gold += inv.list[inp - 1].val * 3;
		}
		else if (inv.list[inp - 1].name == "gorbo's kidney" && inv.list[inp - 1].nom == 1) {
			gold += inv.list[inp - 1].val * 2;
		}
		else {
			gold += inv.list[inp - 1].val/2;
		}
		shop.add(inv.list[inp - 1]);
		inv.sub(inv.list[inp - 1]);
	}
}

void invInt() { // defines the interaction with the inventory
	int i = 0;
	int inp;
	cout << "inventory: \n";
	for (const Item& item : inv.list) {
		i++;
		cout << i << ". " << item.name << " x" << item.nom << " - price: " << item.val << "\n";
	}
	cout << inv.list.size() + 1 << ". back \n";
	while (1) {
		cin >> inp;
		if (cin.fail()) {
			//Not an int.
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (0 < inp && inp <= inv.list.size() + 1) {
			break;
		}
		cout << "invalid \n";
	}
	if (inp < inv.list.size() + 1) {
		cout << inv.list[inp - 1].name << "\ndescription: \n" << "  -  \"" << inv.list[inp - 1].desc << "\" \n";
	}
};


typedef void (*voidFunctionType)(void);

struct Function {
	string name;
	voidFunctionType func;
	Function(string name, voidFunctionType func) {
		this->name = name;
		this->func = func;
	}
};

vector<Function> commands = {Function("buy", shopBuy), Function("sell", shopSell), Function("inventory", invInt)};

void gorbo() {
	cout << "shopkeep: hi, my name is gorbo \n";
	int x;
	int life = 2;
	bool trueEnd = 0;
	while (1) {
		cout << "life: " << life << "\n";
		int i = 0;
		int inp;
		bool areKidneysThere = 0;
		cout << "gold: " << gold << "\n";
		for (Function& x : commands) {
			i++;
			cout << i << ". " << x.name << "\n";
		}
		while (1) {
			cin >> inp;
			if (cin.fail()) { //Not an int.
				cin.clear();
				cin.ignore(256, '\n');
			}
			if (0 < inp && inp <= commands.size()) {
				break;
			}
			cout << "invalid \n";
		}
		commands[inp - 1].func();
		for (const Item& x : shop.list) {
			if (x.name == "gorbo's kidney") {
				areKidneysThere = 1;
				if (x.nom == 2) {
					if (life < 3) {
						life += 1;
					}
				} 
			}
		}
		if (areKidneysThere == 0) {
			life -= 1;
			cout << "\"im dying\" gorbo says \n";
		}
		if (life == 0) {
			if (shop.list.size() == 0) {
				cout << "you stand over gorbo's cold dead body as you hold his kidneys \n" << "you sit down at the stand and set the items to their displays \n" << "you are now gorbo";
				break;
			}
			else {
				cout << "\"you are not worthy\" gorbo says as he tears his kidneys from your hands \n" << "gorbo stands over your near lifeless body stuffing his own kidneys back into his abdomen";
				break;
			}
		}
	}
}

int main() {
	shop = Inventory({
		Item("apple", 10, 2, "a plump apple picked from the orchard"),
		Item("iron broadsword", 80, 1, "the sword of a hero long passed"),
		Item("gorbo's kidney", 50, 2, "gorbo's own kidneys taken willingly from his abdomen"),
		Item("'gorbo's' kidney", 30, 2, "a kidney seemingly belonging to gorbo, two are still warm")
		});
	inv = Inventory({
		Item("duck", 30, 3, "a duck caught recently, it's feathers still unplucked")
		});
	gorbo();
}