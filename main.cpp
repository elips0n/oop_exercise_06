#include<iostream>
#include<algorithm>
#include<locale.h>
#include"list.h"
#include"allocator.h"
#include"triangle.h"

void Menu1() {
	std::cout << "1. Добавить фигуру в список\n";
	std::cout << "2. Удалить фигуру\n";
	std::cout << "3. Вывести фигуру\n";
	std::cout << "4. Вывести все фигуры с помощью std::for_each()\n";
}

void PushMenu() {
	std::cout << "1. Добавить фигуру в начало списка\n";
	std::cout << "2. Добавить фигуру в конец списка\n";
	std::cout << "3. Добавить фигуру по индексу\n";
}

void DeleteMenu() {
	std::cout << "1. Удалить фигуру в начале списка\n";
	std::cout << "2. Удалить фигуру в конце списка\n";
	std::cout << "3. Удалить фигуру по индексу\n";
}

void PrintMenu() {
	std::cout << "1. Вывести первую фигуру в списке\n";
	std::cout << "2. Вывести последнюю фигуру в списке\n";
	std::cout << "3. Вывести фигуру по индексу\n";
}

int main() {
	containers::list<Triangle, allocators::my_allocator<Triangle, 500>> MyList;

	Triangle TempTriangle;
	uint fc = 1;

	while (true) {
		Menu1();
		int n, m, ind;
		double s;
		std::cin >> n;
		switch (n) {
		case 1:
			TempTriangle.Read(std::cin);
			PushMenu();
			std::cin >> m;
			switch (m) {
			case 1:
				MyList.push_front(TempTriangle);
				break;
			case 2:
				MyList.push_back(TempTriangle);
				break;
			case 3: 
				std::cout << "Введите индекс позиции: ";
				std::cin >> ind;
				MyList.insert_by_number(ind, TempTriangle);
			default:
				break;
			}
			break;
		case 2:
			DeleteMenu();
			std::cin >> m;
			switch (m) {
			case 1:
				MyList.pop_front();
				break;
			case 2:
				MyList.pop_back();
				break;
			case 3:
				std::cout << "Введите индекс позиции: ";
				std::cin >> ind;
				MyList.delete_by_number(ind);
				break;
			default:
				break;
			}
			break;
		case 3: 
			PrintMenu();
			std::cin >> m;
			switch (m) {
			case 1:
				MyList.front().Print();
				std::cout << std::endl;
				break;
			case 2:
				MyList.back().Print();
				std::cout  << std::endl;
				break;
			case 3:
				std::cout << "Введите индекс позиции: ";
				std::cin >> ind;
				MyList[ind].Print();
				std::cout  << std::endl;
				break;
			default:
				break;
			}
			break;
		case 4:
			if (MyList.length() == 0)
			{
				std::cout << "Список пуст.\n" << std::endl;
				break;
			}
			fc = 0;
			std::for_each(MyList.begin(), MyList.end(), [fc](Triangle &X) mutable {std::cout << "\n Фигура № " << fc << std::endl; X.Print(); std::cout << std::endl; fc++; });
		break;
		default:
			return 0;
		}
	}

	system("pause");
	return 0;
}
