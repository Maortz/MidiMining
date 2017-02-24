#pragma once
#include "Note.h"

class NoteSeries;
class Midi;

class MidiParser
{
	char * m_midi_buff;
	Midi *m_midi;
	short m_channels;
	NoteSeries *m_note_series_channels[16];

public:

	MidiParser(char* midi, int len);
	~MidiParser();

	inline bool isValid() { return (m_midi == 0 ? false : m_midi->m_is_valid); }
	inline short get_channels() { return m_channels; }
	// TODO: impl
	bool getNotes(NoteSeries* notes, int channel);

};

