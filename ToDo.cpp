#include <conio.h>
#include <iostream>
#include "Task.h"
using namespace std;
int main()
{
	int N = 0;
	Task* list;
	readFromFile(list, N, "ToDo.txt");

	menu(list, N);
	writeToFile(list, N, "ToDo.txt");
}