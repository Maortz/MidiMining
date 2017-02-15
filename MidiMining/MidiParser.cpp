#include "MidiParser.h"
#include <string.h>

MidiParser::MidiParser(char* midi, int len)
{
	m_midi = new char[len];
	memcpy(m_midi, midi, len);
}


MidiParser::~MidiParser()
{
}
