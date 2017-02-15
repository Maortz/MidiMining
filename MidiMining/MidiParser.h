#pragma once
class MidiParser
{
	char * m_midi;

	class TrackEvent
	{
		unsigned int delta_time;
		// midi_event:  status, 0x80 - 0xEF
		// meta_event:  0xFF
		// sysex_event: 0xF0
		char status;
		char* data;
	};
	struct TrackChunk
	{
		char MTrk[4];
		int track_length;
		char* events;
	};
	struct HeaderChunk
	{
		char MThd[4];
		int header_length;
		short format;
		short number_of_tracks;
		short division;
	};

public:
	MidiParser(char* midi, int len);
	~MidiParser();
};

