#pragma once
#include "Note.h"
#include <vector>

class NoteSeries
{
	
public:
	std::vector<Note*> notes;
	unsigned int instrument_type;
	unsigned int scale;

	NoteSeries();
	~NoteSeries();

	void sort();
	unsigned int commonLinkedInterval();
	unsigned int commonMostInterval();
};

