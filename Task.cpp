#include <iostream>
#include "Task.h"
#include <fstream>
#include <conio.h>
using std::cout;
using std::cin;
using std::endl;
using namespace std;

void setTask(Task& obj)
{
	char tempName[70];
	cout << "Enter new task name" << endl;
	cin.getline(tempName, 70);
	cin.clear();
	int n = strlen(tempName);
	obj.taskName = new char[n + 1];
	strcpy_s(obj.taskName, static_cast<rsize_t>(n) + 1, tempName);
	cout << "------------------------------------------------------\n";
	cout << "Enter priority: 1 - low, 2 - middle, 3 - high, 4 - top\n";
	cin >> obj.priority;
	cout << "------------------------------------------------------\n";
	cin.ignore();
	char description[1000];
	cout << "Enter description" << endl;
	cin.getline(description, 1000);
	cin.clear();
	int m = strlen(description);
	obj.description = new char[m + 1];
	strcpy_s(obj.description, static_cast<rsize_t>(m) + 1, description);
	cout << "------------------------------------------------------\n";
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> obj.execution.day >> obj.execution.month >> obj.execution.year;
	cout << "Enter task execution time hh:mm ";
	cin >> obj.execution.hour >> obj.execution.min;
	cout << "Enter task reminder time hh:mm ";
	cin >> obj.reminder.hour >> obj.reminder.min;
	cin.ignore();
}

void setTask(Task*& obj, int& size)
{
	Task* addTask = new Task[size + 1]; 
	for (int i = 0; i < size; i++)
	{
		addTask[i].execution = obj[i].execution;
		addTask[i].taskName = new char[strlen(obj[i].taskName) + 1];
		strcpy_s(addTask[i].taskName, strlen(obj[i].taskName) + 1, obj[i].taskName);
		delete[] obj[i].taskName;
		addTask[i].priority = obj[i].priority;
		addTask[i].description = new char[strlen(obj[i].description) + 1];
		strcpy_s(addTask[i].description, strlen(obj[i].description) + 1, obj[i].description);
		delete[] obj[i].description;
		addTask[i].reminder = obj[i].reminder;
	}
	setTask(addTask[size]);
	delete[] obj;

	obj = addTask;
	size++;
}

void getTask(Task& obj)
{
	cout << "\n----------------------------------------------------------------\n";
	(obj.execution.hour < 10) ? cout << "0" << obj.execution.hour : cout << obj.execution.hour;
	cout << ":";
	(obj.execution.min < 10) ? cout << "0" << obj.execution.min : cout << obj.execution.min;
	cout << " | ";
	(obj.execution.day < 10) ? cout << "0" << obj.execution.day : cout << obj.execution.day;
	cout << ".";
	(obj.execution.month < 10) ? cout << "0" << obj.execution.month : cout << obj.execution.month;
	cout << "." << obj.execution.year;
	cout << " | ";
	cout << "Name:  " << obj.taskName << " | ";
	switch (obj.priority)
	{
	case priority::low: cout << "Low";
		break;
	case priority::middle: cout << "Middle";
		break;
	case priority::high: cout << "High";
		break;
	case priority::top: cout << "Top";
		break;
	}
	cout << " priority\n";
	cout << "Description: " << obj.description << endl;
	cout << "     Reminder time ";
	(obj.reminder.hour < 10) ? cout << "0" << obj.reminder.hour : cout << obj.reminder.hour;
	cout << ":";
	(obj.reminder.min < 10) ? cout << "0" << obj.reminder.min : cout << obj.reminder.min;
	cout << endl;
}

void getTask(Task*& obj, int& size)
{
	cout << "-------------------------TASK ORGANIZER-------------------------\n";
	for (int i = 0; i < size; i++)
	{
		cout  << " " << i + 1;
		getTask(obj[i]);
	}
}

void searchTaskByday(Task*& obj, int& size)
{
	int day, month, year;
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> day >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (obj[i].execution.day == day && obj[i].execution.month == month && obj[i].execution.year == year)
		{
			cout << i + 1 << " ";
			getTask(obj[i]);
		}
	}
}

void searchTaskByMonth(Task*& obj, int& size)
{
	int  month, year;
	cout << "Enter task execution mm.yyyy: ";
	cin >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (obj[i].execution.month == month && obj[i].execution.year == year)
		{
			cout << i + 1 << " ";
			getTask(obj[i]);
		}
	}
}

void searchTaskByWeek(Task*& obj, int& size)
{
	int day, month, year;
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> day >> month >> year;

	for (int j = day; j < day + 7; j++)
	{
		for (int i = 0; i < size; i++)
		{
			if (obj[i].execution.day == j && obj[i].execution.month == month && obj[i].execution.year == year)
			{
				cout << i + 1 << " ";
				getTask(obj[i]);
			}
		}
	}
}

void searchTaskByPriority(Task*& obj, int& size)
{
	int p, count = 1;
	cout << "Enter task priority to show\n";
	cout << "1 - Low priority tasks\n2 - Middle priority tasks\n3 - High priority tasks\n4 - Top priority tasks\n";
	cin >> p;
	system("cls");
	cout << "-------------------------Tasks with ";
	switch (p)
	{
	case priority::low: cout << "Low";
		break;
	case priority::middle: cout << "Middle";
		break;
	case priority::high: cout << "High";
		break;
	case priority::top: cout << "Top";
		break;
	}
	cout << "------------------------\n";
	for (int i = 0; i < size; i++)
	{
		if (obj[i].priority == p)
		{
			cout << " " << count++;
			getTask(obj[i]);
		}
	}
}

void searchTaskByTaskName(Task*& obj, int& size)
{
	char name[70];
	bool isFound = false;
	cout << "Enter task name you want to search\n";
	cin.getline(name, 70);
	system("cls");
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(obj[i].taskName, name))
		{
			cout << "Yes, task was found" << endl;
			getTask(obj[i]);
			isFound = true;
			break;
		}
	}

	if (isFound == false)
	{	
		cout << "There is no task with this name.\n";
	}
}

void searchMenu(Task*& obj, int& size)
{
	int a;
	do
	{
		system("cls");
		cout << "------------------------------MENU------------------------------\n";
		cout << "1 - search task by day\n";
		cout << "2 - search task by week\n";
		cout << "3 - search task by month\n";
		cout << "4 - search task by priority\n";
		cout << "5 - search task by task name\n";
		cin >> a;
		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5)
		{
			break;
		}
	} while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5);
	cin.ignore();
	switch (a) {
	case 1:	searchTaskByday(obj, size);
		break;
	case 2:	 searchTaskByWeek(obj, size);
		break;
	case 3:	searchTaskByMonth(obj, size);
		break;
	case 4:	searchTaskByPriority(obj, size);
		break;
	case 5:	searchTaskByTaskName(obj, size);
	}
	menu(obj, size);
}

void changeTask(Task*& obj, int& size)
{
	getTask(obj, size);
	int N;
	do {
		cout << "Enter task number you want to change: ";
		cin >> N;
		cin.ignore();
		if (N > 0 && N <= size)
		{
			delete[] obj[N - 1].taskName;
			delete[] obj[N - 1].description;
			setTask(obj[N - 1]);
		}
	} while (N < 1 || N > size);
}

void deleteTask(Task*& obj, int& size)
{
	getTask(obj, size);
	int N;
	do {
		cout << "Enter task number you want to delete: ";
		cin >> N;
		cin.ignore();
		if (N > 0 && N <= size)
		{
			Task* del = new Task[size - 1];
			for (int i = 0; i < N - 1; i++)
			{
				del[i].execution = obj[i].execution;
				del[i].taskName = new char[strlen(obj[i].taskName) + 1];
				strcpy_s(del[i].taskName, strlen(obj[i].taskName) + 1, obj[i].taskName);
				delete[] obj[i].taskName;
				del[i].priority = obj[i].priority;
				del[i].description = new char[strlen(obj[i].description) + 1];
				strcpy_s(del[i].description, strlen(obj[i].description) + 1, obj[i].description);
				delete[] obj[i].description;
				del[i].reminder = obj[i].reminder;
			}
			for (int i = N - 1; i < size - 1; i++)
			{
				del[i].execution = obj[i + 1].execution;
				del[i].taskName = new char[strlen(obj[i + 1].taskName) + 1];
				strcpy_s(del[i].taskName, strlen(obj[i + 1].taskName) + 1, obj[i + 1].taskName);
				delete[] obj[i + 1].taskName;
				del[i].priority = obj[i + 1].priority;
				del[i].description = new char[strlen(obj[i + 1].description) + 1];
				strcpy_s(del[i].description, strlen(obj[i + 1].description) + 1, obj[i + 1].description);
				delete[] obj[i + 1].description;
				del[i].reminder = obj[i + 1].reminder;
			}
			delete[] obj[N - 1].taskName;
			delete[] obj[N - 1].description;
			delete[] obj;
			obj = del;
		}
	} while (N < 1 || N > size);	
	size--;
}

void sortPriorty(Task*& obj, int size, bool direction)
{
	int k, priority;
	Task temp;
	for (int i = 0; i < size; i++)
	{
		k = i;
		priority = obj[i].priority;
		for (int j = i + 1; j < size; j++)
		{
			if (direction)
			{
				if (obj[j].priority > priority)	k = j, temp = obj[j];
			}
			else
			{
				if (obj[j].priority < priority)	k = j, temp = obj[j];
			}
		}
		if (k != i)
		{
			obj[k] = obj[i];
			obj[i] = temp;
		}
	}
}

void sortTime(Task*& obj, int size, bool direction)
{
	int k, time;
	Task temp;
	for (int i = 0; i < size; i++)
	{
		k = i;
		time = ((obj[i].execution.month - 1) * 30 + obj[i].execution.day) * 24 * 60;
		for (int j = i + 1; j < size; j++)
		{
			if (direction)
			{
				if (((obj[j].execution.month - 1) * 30 + obj[j].execution.day) * 24 * 60 > time)
				{
					k = j;
					temp = obj[j];
				}
			}
			else
			{
				if (((obj[j].execution.month - 1) * 30 + obj[j].execution.day) * 24 * 60 < time)
				{
					k = j;
					temp = obj[j];
				}
			}
		}
		if (k != i)
		{
			obj[k] = obj[i];
			obj[i] = temp;
		}
	}
}

void sortMenu(Task*& obj, int& size)
{
	int a;	
	do
	{
		system("cls");
		cout << "------------------------------MENU------------------------------\n";
		cout << "1 - sort by execution time, latest on top\n";
		cout << "2 - sort by execution time, erliest on top\n";
		cout << "3 - sort by priority, from high to low\n";
		cout << "4 - sort by priority, from low to high\n";
		
		cin >> a;
		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5)
		{
			break;
		}
	} while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5);
	switch (a)
	{
	case  1: sortTime(obj, size, 1);
		break;
	case  2: sortTime(obj, size, 0);
		break;
	case  3: sortPriorty(obj, size, 1);
		break;
	case  4: sortPriorty(obj, size, 0);
		break;	
	}
	getTask(obj, size);
	menu(obj, size);
}



void writeToFile(Task* obj, int& size,const char* fileName)
{
	ofstream taskToFile;
	taskToFile.open(fileName, ios::out);
	if (!taskToFile.is_open())
	{
		cout << "To do list is empty.";
		return;
	}

	taskToFile << size << endl;
	for (int i = 0; i < size; i++)
	{
		taskToFile << obj[i].execution.hour << '\t';
		taskToFile << obj[i].execution.min << '\t';
		taskToFile << obj[i].execution.day << '\t';
		taskToFile << obj[i].execution.month << '\t';
		taskToFile << obj[i].execution.year << '\t';

		int nameSize = strlen(obj[i].taskName);
		int descriptionSize = strlen(obj[i].description);
		
		taskToFile << nameSize << '\t';
		taskToFile << obj[i].taskName<< '\t';
		taskToFile << obj[i].priority<< '\t';
		taskToFile << descriptionSize << '\t';
		taskToFile << obj[i].description<< '\t';
		taskToFile << obj[i].reminder.hour<< '\t';
		taskToFile << obj[i].reminder.min<< '\t';
		if (i < size - 1) taskToFile << endl;
	}	
	taskToFile.close();
}

void readFromFile(Task* &obj, int& size, const char* fileName)
{
	ifstream taskFromFile;
	taskFromFile.open(fileName, ios::in);
	if (!taskFromFile.is_open())
	{
		cout << "To do list is empty. Write first task\n";
		return;
	}
	int N = 0;
	taskFromFile >> N;
	Task* ruturnToWork = new Task[N];
	int i = 0;
	for (int i = 0; i < N; i++)
	{
		int nameSize = 0;
		int descriptionSize = 0;
		taskFromFile >> ruturnToWork[i].execution.hour;
		taskFromFile >> ruturnToWork[i].execution.min;
		taskFromFile >> ruturnToWork[i].execution.day;
		taskFromFile >> ruturnToWork[i].execution.month;
		taskFromFile >> ruturnToWork[i].execution.year;
		taskFromFile >> nameSize;
		taskFromFile.ignore();
		ruturnToWork[i].taskName = new char[nameSize + 1];
		taskFromFile.getline(ruturnToWork[i].taskName, nameSize + 1);
		taskFromFile.clear();
		taskFromFile >> ruturnToWork[i].priority;
		taskFromFile >> descriptionSize;
		taskFromFile.ignore();
		ruturnToWork[i].description = new char[descriptionSize + 1];
		taskFromFile.getline(ruturnToWork[i].description, descriptionSize + 1);
		taskFromFile.clear();
		taskFromFile >> ruturnToWork[i].reminder.hour;
		taskFromFile >> ruturnToWork[i].reminder.min ;
	}	
	taskFromFile.close();
	obj = ruturnToWork;
	size = N;
}

void menu(Task*& obj, int& size)
{
	int a;
	cout << "Press any button to see menu\n";
	a = _getch();
	do
	{
		system("cls");
		cout << "------------------------------MENU------------------------------\n";
		cout << "1 - add Task\n";
		cout << "2 - edit Task\n";
		cout << "3 - delete Task\n";
		cout << "4 - search Task\n";
		cout << "5 - sort Task\n";
		cin >> a;
		cin.ignore();
		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5)
		{
			break;
		}
	} while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5);
	switch (a)
	{
	case  1: setTask(obj,size);
		break;
	case  2: changeTask(obj,size);
		break;
	case  3: deleteTask(obj,size);
		break;
	case  4: searchMenu(obj,size);
		break;
	case  5: sortMenu(obj,size);
		break;
	}
	menu(obj, size);
}



