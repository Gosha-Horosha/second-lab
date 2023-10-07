#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <windows.h> // для русификации
using namespace std;
const int MAX = 50;

//=======     class House     =================

class House {          
	char address[MAX];
	int floor;
	int rooms;
	double square;
public:
	char* get() {
		return address;
	}
	int getfl() {
		return floor;
	}
	int getro() {
		return rooms;
	}
	double getsq() {
		return square;
	}
	void set(char address[MAX], int floor, int rooms, double square);
	void show();
	~House() { cout << "destructor\n"; }
	House();
	House(char[], int, int, double);
};
House::House() {
	strcpy_s(this->address, "foiehfe");
	this->floor = 0;
	this->rooms= 0;
	this->square = 0;
}
House::House(char address[MAX], int floor, int rooms, double square) {
	strcpy_s(this->address, address);
	this->floor = floor;
	this->rooms = rooms;
	this->square = square;
}
void House::show() {
	cout << "| " << setw(23) << address << "    | " << setw(7) << floor << "   |  ";
	cout << setw(2) << rooms << "   | " << setw(5) << square << "    | " << endl;
}
void House::set(char addr[MAX], int fl, int rms, double sq) {
	strcpy_s(this->address, addr);
	this->floor = fl;
	this->rooms = rms;
	this->square = sq;
}
//-------вывод шапки--------------------------------------------------
void shapka() {
	cout << "|-----------------------------------------------------------|" << endl;
	cout << "|          address           |   floor   | rooms |  square  |" << endl;
	cout << "|-----------------------------------------------------------|" << endl;
}
//------список всех студентов-------------------------------------
void print(House* spis, int n) {
	shapka();
	for (int i = 0; i < n; i++)
		spis[i].show();
}
void print(House* spis, int n,int room) {
	shapka();
	for (int i = 0; i < n; i++)
		if(spis[i].getro()==room)
		spis[i].show();
}
void print(House* spis, int n, int room,int floorbeg, int floorend) {
	shapka();
	for (int i = 0; i < n; i++)
		if (spis[i].getro() == room && spis[i].getfl() >= floorbeg && spis[i].getfl() <= floorend)
			spis[i].show();
}
void print(House* spis, int n, double square) {
	shapka();
	for (int i = 0; i < n; i++)
		if (spis[i].getsq() > square)
			spis[i].show();
}


//=========    main   ================


int main() {
//========  Русификаця  ===============
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);  
	SetConsoleOutputCP(1251);
	const int NH = 3;
	char tx[MAX];
	int numHouse;
	char address[MAX];
	char addressnum[NH];
	int numberOfRooms;
	double area;
	int floor;
	int houseCount = 0;

	cout << "Enter num of Houses from 1 to 9\n ";
	cin >> numHouse;
	House* array = new House[numHouse];

	ifstream file("home.txt", ios::out);
	if (!file) { cerr << "No file open\n"; exit(1); }
	while (!file.eof()) {
		file.getline(tx, MAX);
		if (!file.eof()) cout << tx << '\n';
	}
	cout << tx<< '\n';
	file.close();

	ifstream file2("home.txt", ios::out);
    if (!file2) { cerr << "No file open\n"; exit(1); }
	while (houseCount < numHouse &&
		file2 >> address >> addressnum >> floor >> numberOfRooms >> area) {
		strcat_s(address, sizeof(address), " ");
		strcat_s(address,sizeof(address), addressnum);
		array[houseCount].set(address, floor, numberOfRooms, area); 
		houseCount++;
	}
	file2.close();

	print(array, numHouse);
	int flag = 1, select;
	while (flag) {
		cout << "select num case (1-4)" << endl;
		cout << "1-print all spisok" << endl;
		cout << "2-print from room number" << endl;
		cout << "3-print from room and the floor" << endl;
		cout << "4-print by square" << endl;
		cout << "5-end the program" << endl;
		cin >> select;
		switch (select) {
		case 1: 
			print(array, numHouse);
			break;
		case 2: 
			int room;
			cout << "Enter room number ";
			cin >> room;
			print(array, numHouse, room);
			break;
		case 3: {
			int room,beg,end;
			cout << "Enter room number ";
			cin >> room;
			cout << "Enter interval of floors(2 num) ";
			cin >> beg >> end;
			print(array, numHouse, room,beg,end);
			break;
		}
		case 4:
		{
			double squ;
			cout << "Enter square ";
			cin >> squ;
			print(array, numHouse, squ);
			break;
		}
		case 5: 
			flag = 0; 
			for (int i=0; i < numHouse; i++)
				array[i].~House();
			delete[] array;
			break;
		}
	}
	cout << " End program" << endl;
}

/*
Сергей Александрович 
1 русификация
2 динамическая память
(класс деструктор)
3 меню switch case
4 1пункт меню - чтение и вывод файла

