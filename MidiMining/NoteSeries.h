#pragma once
#include "Note.h"
#include <vector>

class NoteSeries
{
	
public:
	std::vector<Note*> notes;

	NoteSeries();
	~NoteSeries();

	void sort();
	unsigned int commonLinkedInterval();
	unsigned int commonMostInterval();
};

