#include "Note.h"


Note::Note() :m_semitones(0), m_duration(0)
{
}


Note::~Note()
{
}

int Note::getInterval(Note &note1, Note &note2)
{
	return note1.m_semitones - note2.m_semitones;
}

double Note::endBarPosition()
{
	return m_bar_position + m_duration;
}

double Note::endStartPosition()
{
	return m_start_position + m_duration;
}

double Note::ppqnToDuration(unsigned int division, unsigned int ppqn)
{
	double whole = division * 4;
	return (ppqn / whole);
}

int Note::octaveFromMiddle()
{
	return (m_semitones / 12) - 5;
}

void Note::noteSign(char* buff)
{
	int note = m_semitones % 12;
	char c = 'C';
	if (note <= 4)
		++note;
	buff[0] = c + note / 2;
	buff[1] = note % 2 == 0 ? '\0' : '#';
	buff[2] = '\0';
}