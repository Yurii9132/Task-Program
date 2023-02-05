#pragma once
struct DataTask
{
	int min;
	int hour;
	int day;
	int month;
	int year;
};
enum priority
{
	low = 1, middle, high, top
};
struct Task
{
	DataTask execution;
	char* taskName;
	int priority;
	char* description;
	DataTask reminder;
};



void setTask(Task& obj);
void setTask(Task*& obj, int& size);
void getTask(Task& obj);
void getTask(Task*& obj, int& size);
void changeTask(Task*& obj, int& size);
void deleteTask(Task*& obj, int& size);

void searchTaskByday(Task*& obj, int& size);
void searchTaskByMonth(Task*& obj, int& size);
void searchTaskByWeek(Task*& obj, int& size);
void searchTaskByPriority(Task*& obj, int& size);
void searchTaskByTaskName(Task*& obj, int& size);
void searchMenu(Task*& obj, int& size);

void sortPriorty(Task*& obj, int size, bool direction = true);
void sortTime(Task*& obj, int size, bool direction = true);
void sortMenu(Task*& obj, int& size);

void writeToFile(Task* obj, int& size, const char* fileName);
void readFromFile(Task* &obj, int& size, const char* fileName);

void menu(Task*& obj, int& size);
