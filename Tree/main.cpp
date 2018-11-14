#include "map_.h"
#include <string>


void main()
{
	map_<int, string> m;
	m.insert(8, "8");
	m.insert(3, "8");
	m.insert(10, "8");
	m.insert(1, "8");
	m.insert(9, "8");
	m.insert(7, "8");
	m.insert(5, "8");
	m.insert(4, "8");
	m.insert(6, "8");
	m.insert(14, "8");
	m.insert(13, "8");
	m.insert(11, "8");
	m.insert(20, "8");
	m.insert(15, "8");
	m.insert(25, "8");
	m.insert(17, "8");
	m.insert(16, "8");
	m.insert(19, "8");
	//m.print();
	//string a = m.find(5);
	//cout << a << endl;

	//cout << m.findMax();
	
	//cout << m.prevElement(5)->key;

	m.erase(10);
	m.print();
	
	
	
	
	
	system("pause");
}