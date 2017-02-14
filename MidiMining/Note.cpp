#include "Note.h"


Note::Note() :m_semitones(0), m_duration(0)
{
}


Note::~Note()
{
}

void Note::set_semitones(unsigned int semitones)
{
	m_semitones = semitones;
}

unsigned int Note::get_semitones()
{
	return m_semitones;
}

void Note::set_duration(unsigned int duration)
{
	m_duration = duration;
}

unsigned int Note::get_duration()
{
	return m_duration;
}

int Note::GetInterval(Note note1, Note note2)
{
	return note1.m_semitones - note2.m_semitones;
}