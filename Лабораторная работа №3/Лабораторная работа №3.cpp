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
	int position = 0;
	Node* last = nullptr;

	void toPreposition(int number) {
		while (position != number) {
			if (number == 0 && position == counting) { break; }
			last = last->next;
			position++;
			if (position > counting) { position = 1; }
		}
	}
	void add(int value) {
		toPreposition(counting);
		Node* node = new Node();
		node->param = value;
		if (counting == 0) {
			last = node;
			last->next = node;
		}
		else {
			node->next = last->next;
			last->next = node;
			last = node;
		}
		counting++;
		position++;
	}
	void insert(int index, int value) {
		if (index == counting) {
			add(value);
			return;
		}
		toPreposition(index);
		Node* node = new Node();
		node->param = value;
		node->next = last->next;
		last->next = node;
		last = node;
		position++;
		if (position > counting) { position = 1; }
		counting++;
	}
	int elementAt(int index) {
		toPreposition(index);
		return last->next->param;
	}
	void removeAt(int index) {
		toPreposition(index);
		Node* del = last->next;
		last->next = del->next;
		delete del;
		counting--;
		if (position > counting) { position = counting; }
		if (counting == 0) { last = nullptr; }
	}
	void insertBeforeNegative() {
		int kol = counting;
		for (int i = 0; i < kol; i++) {
			if (last->next->param < 0) {
				if (position != counting) { insert(position, 1); }
				else { insert(0, 1); }
			}
			last = last->next;
			position++;
			if (position > counting) { position = 1; }
		}
	}
	void removeNegative() {
		if (counting == 0) { return; }
		int kol = counting;
		for (int i = 0; i < kol; i++) {
			if (last->next->param < 0) { removeAt(position); }
			else {
				last = last->next;
				position++;
				if (position > counting) { position = 1; }
			}
		}
	}
	int count(int value) {
		int ans = 0;
		for (int i = 0; i < counting; i++) {
			if (last->param == value) { ans++; }
			last = last->next;
		}
		return ans;
	}
	void clear() {
		for (int i = 0; i < counting; i++) {
			Node* del = last->next;
			last->next = del->next;
			delete del;
		}
		last = nullptr;
		counting = 0;
		position = 0;
	}
	int count() { return counting; }
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
			cout << "Список очищен\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Неизвестная команда!\n";
		}
	}
}
