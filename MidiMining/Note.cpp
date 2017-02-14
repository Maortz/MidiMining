#include "Note.h"


Note::Note() :m_semitones(0), m_duration(0)
{
}


Note::~Note()
{
}

int Note::getInterval(Note note1, Note note2)
{
	return note1.m_semitones - note2.m_semitones;
}