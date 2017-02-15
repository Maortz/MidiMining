#include "MidiParser.h"
#include <string.h>

MidiParser::MidiParser(char* midi, int len) : m_track_count(0), m_events_count(0), m_is_valid(false)
{
	m_midi = new char[len];
	memcpy(m_midi, midi, len);
}


MidiParser::~MidiParser()
{
}

bool MidiParser::parseIt()
{
	m_is_valid = true;
	return true;
}

short MidiParser::getChannels()
{

}

bool MidiParser::getNotes(NoteSeries* notes, int channel)
{

}

bool MidiParser::isValid()
{
	return m_is_valid;
}