#include <iostream>
using namespace std;

void instruction() {
	cout << "Для добавления элемента в очередь, введите 1\n";
	cout << "Для вставки в данную позицию данного значения, введите 2\n";
	cout << "Для удаления элемента из данной позиции, введите 3\n";
	cout << "Для доступа к числу в данной позиции, введите 4\n";
	cout << "Для подсчета количества элементов в списке, введите 5\n";
	cout << "Для вставки перед каждым отрицательным элементом числа 1, введите 6\n";
	cout << "Для удаления отрицательных элементов из списка, введите 7\n";
	cout << "Для подсчета количества конкретного элемента в списке, введите 8\n";
	cout << "Для очистки всего списка, введите 9\n";
	cout << "Для завершения работы программы, введите 0\n\n";
}

struct Node {
	int param = 0;
	Node* next = nullptr;
};

struct List {
	int counting = 0;
	Node* last = nullptr;

	int count() {
		return counting;
	}
	int count(int value) {
		int ans = 0, kol = count();
		Node* node = last->next;
		for (int i = 0; i < kol; i++) {
			if (node->param == value) { ans++; }
			node = node->next;
		}
		return ans;
	}
	void add(int value) {
		Node* node = new Node();
		node->param = value;
		if (count() == 0) { 
			last = node; 
			last->next = node;
		}
		else {
			node->next = last->next;
			last->next = node;
			last = node;
		}
		counting++;
	}
	void clear() {
		int kol = count();
		for (int i = 0; i < kol; i++) {
			Node* del = last->next;
			last->next = del->next;
			delete del;
		}
		last = nullptr;
		counting = 0;
	}
	void removeNegative() {
		int kol = count();
		if (kol == 0) { return; }
		Node* lastElement = last;
		Node* node = last;
		while(true) {
			Node* del = node;
			if (node->next == lastElement) { // Для последнего
				if (lastElement->param < 0) {
					node->next = lastElement->next;
					delete lastElement;
					counting--;
				}
				else { last = lastElement; }
				break;
			}
			if (node->next->param < 0) { // Общий случай
				del = node->next;
				node->next = node->next->next;
				delete del;
				counting--;
			}
			else { node = node->next; }
			last = node;
		}
		if (count() == 0) { last = nullptr; }
	}
	void insertBeforeNegative() {
		if (count() == 0) { return; }
		Node* node = last;
		while (true) {
			if (node->next->param < 0) {
				Node* add = new Node();
				counting++;
				add->param = 1;
				add->next = node->next;
				node->next = add;
				node = add;
			}
			node = node->next;
			if (node == last) { break; }
		}

	}
	void insert(int index, int value) {
		if (index == count() || count() == 0) {
			add(value);
			return;
		}
		Node* node = last;
		for (int i = 0; i < index; i++) { node = node->next; }
		Node* insert = new Node();
		counting++;
		insert->param = value;
		insert->next = node->next;
		node->next = insert;
	}
	void removeAt(int index) {
		Node* node = last;
		for (int i = 0; i < index; i++) { node = node->next; }
		Node* del = node->next;
		node->next = del->next;
		if (del == last) { last = node; }
		delete del;
		counting--;
		if (count() == 0) { last = nullptr; }
	}
	int elementAt(int index) {
		Node* node = last;
		for (int i = 0; i < index; i++) { node = node->next; }
		return node->next->param;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	List list;
	instruction();
	while (true) {
		cout << "\nВведите команду: ";
		int parametr;
		cin >> parametr;
		switch (parametr) {
		case 1:
			cout << "Введите число: ";
			int num;
			cin >> num;
			list.add(num);
			break;
		case 2:
			cout << "Введите позицию: ";
			int pozition;
			cin >> pozition;
			if (pozition > list.count() || pozition < 0) {
				cout << "Некорректная позиция!\n";
			}
			else {
				cout << "Введите число: ";
				int value;
				cin >> value;
				list.insert(pozition, value);
			}
			break;
		case 3:
			cout << "Введите позицию: ";
			cin >> pozition;
			if (pozition >= list.count() || pozition < 0) {
				cout << "Некорректная позиция!\n";
			}
			else {
				list.removeAt(pozition);
			}
			break;
		case 4:
			cout << "Введите позицию: ";
			cin >> pozition;
			if (pozition >= list.count() || pozition < 0) {
				cout << "Некорректная позиция!\n";
			}
			else {
				cout << "Элемент:" << list.elementAt(pozition) << endl;
			}
			break;
		case 5:
			cout << "Количество элементов: " << list.count() << endl;
			break;
		case 6:
			list.insertBeforeNegative();
			break;
		case 7:
			list.removeNegative();
			break;
		case 8:
			cout << "Введите число: ";
			cin >> num;
			cout << "Количество: " << list.count(num) << endl;
			break;
		case 9:
			list.clear();
			cout << "Очередь очищена\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Неизвестная команда!\n";
		}
	}
}
