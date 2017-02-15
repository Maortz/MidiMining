#pragma once
class NoteSeries;

class MidiParser
{
	char * m_midi;

	class TrackEvent
	{

		int m_buff_len;
		bool m_is_valid;
	public:
		unsigned int m_delta_time;
		// midi_event:  status, 0x80 - 0xEF
		// meta_event:  0xFF
		// sysex_event: 0xF0
		char m_status;
		char* m_data;
		//
		// Set all in the Ctor
		TrackEvent(char* buff);
		~TrackEvent();
		inline bool isValid() { return m_is_valid; }
		inline int get_buff_len() { return m_buff_len; }
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
		char* data;
	};
	HeaderChunk* m_header_chunk;
	unsigned int m_track_count;
	TrackChunk** m_track_chunk;
	unsigned int **m_events_count;
	TrackEvent*** m_track_event;
	short m_channels;
	bool m_is_valid;

	bool Destroy();
	bool headerIsValid();
	bool trackIsValid(int i);

	const int m_mini_event_bytes = 4;
	void shrinkTrackEventArray(int i);
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
	short get_channels();
	bool getNotes(NoteSeries* notes, int channel);

};

