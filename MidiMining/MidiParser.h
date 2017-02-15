#pragma once
class NoteSeries;

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
	HeaderChunk* m_header_chunk;
	TrackChunk* m_track_chunk;
	unsigned int m_track_count;
	TrackEvent* m_track_event;
	unsigned int **m_events_count;
	bool m_is_valid;
public:

	const char ShortBits[] = {
		0x0001,
		0x0002,
		0x0004,
		0x0008,
		0x0010,
		0x0020,
		0x0040,
		0x0080,
		0x0100,
		0x0200,
		0x0400,
		0x0800,
		0x1000,
		0x2000,
		0x4000,
		0x8000
	};

	MidiParser(char* midi, int len);
	~MidiParser();

	bool isValid();
	bool parseIt();
	short getChannels();
	bool getNotes(NoteSeries* notes, int channel);

};

