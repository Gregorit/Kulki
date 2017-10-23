#pragma once
#include <string>
using namespace std;

struct Element
{
	string playerName;
	int poi; //poi -- points
	Element *next;
};
class Ranking
{
private:
	Element *head;
public:
	Ranking();
	void add(string playerName, int poi);
	int loadRanking();
	void sort();
	void saveRanking();
	void write();
};