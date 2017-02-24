#include "MidiParser.h"
#include "NoteSeries.h"

MidiParser::MidiParser(char* midi, int len) : m_channels(0)
{
	m_midi_buff = new char[len];
	for (size_t i = 0; i < 16; i++)
		m_note_series_channels[i] = 0;
	memcpy(m_midi_buff, midi, len);
}

MidiParser::~MidiParser()
{
	delete m_midi_buff;
}
