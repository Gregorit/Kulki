#include <iostream>
#include "Ranking.h"
#include "Board.h"

void Ranking::saveRanking()
{
	FILE *rankingSave;
	rankingSave = fopen("ranking.txt", "w");
	Element *pointer = head;
	while (pointer != NULL)
	{
		fprintf(rankingSave, "%s ", pointer->playerName.c_str());
		fprintf(rankingSave, "%d\n", pointer->poi);
		pointer = pointer->next;
	}
	fclose(rankingSave);
}

int Ranking::loadRanking()
{
	FILE *rankingLoad;
	rankingLoad = fopen("ranking.txt", "r");
	if (rankingLoad == NULL)
		return 0;
	char character = getc(rankingLoad);
	if (character == EOF)
		return 0;
	rewind(rankingLoad);

	Element *pointer=NULL;
	while (!feof(rankingLoad))
	{
		if (head == NULL)
		{
			pointer=head = new Element();
			char auxiliaryArray[100];
			fscanf(rankingLoad, "%s", auxiliaryArray);
			head->playerName = string(auxiliaryArray);
			fscanf(rankingLoad, "%d\n", &head->poi);
			head->next = NULL;
		}
		else
		{
			pointer->next = new Element();
			pointer = pointer->next;
			char auxiliaryArray[100];
			fscanf(rankingLoad, "%s", auxiliaryArray);
			pointer->playerName = string(auxiliaryArray);
			fscanf(rankingLoad, "%d\n", &pointer->poi);
			pointer->next = NULL;
		}
	}
	fclose(rankingLoad);
	sort();
}

void Ranking::sort()
{
	Element *pointer = head, *aux = NULL, *auxHead = NULL; //aux - auxiliary
	while (pointer != NULL && pointer->next != NULL)
	{
		if (pointer->poi < pointer->next->poi)
		{
			if (head == pointer)
			{
				head = pointer->next;
				pointer->next = pointer->next->next;
				head->next = pointer;
				pointer = head;
			}
			else
			{
				aux = pointer->next;
				auxHead->next = aux;
				pointer->next = pointer->next->next;
				aux->next = pointer;
				pointer = head;
				continue;
			}
		}
		auxHead = pointer;
		pointer = pointer->next;
	}
}

void Ranking::add(string playerName, int poi) // poi - points
{
	if (head == NULL)
	{
		head = new Element();
		head->playerName = playerName;
		head->poi = poi;
		head->next = NULL;
	}
	else
	{
		Element *pointer = head;
		while (pointer->next != NULL)
			pointer = pointer->next;
		pointer->next = new Element();
		pointer = pointer->next;
		pointer->playerName = playerName;
		pointer->poi = poi;
		pointer->next = NULL;
	}
	sort();
	saveRanking();
}

Ranking::Ranking() :head(NULL)
{
	loadRanking();
};

void Ranking::write()
{
	Element *pointer = head;
	while (pointer!= NULL)
	{
		cout << pointer->playerName << " ";
		cout << pointer->poi << endl;
		pointer = pointer->next;
	}
}