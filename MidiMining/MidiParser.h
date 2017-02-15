#pragma once
class NoteSeries;

class MidiParser
{
	char * m_midi_buff;
	struct TrackChunk
	{
		char MTrk[4];
		int track_length;
		char* data;
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

	class Event
	{
	public:
		//
		// Set all in the Ctor
		Event(char* event_buff);
		~Event();
		bool parse();
		inline int get_delta_time() { return m_delta_time; }
		inline char get_status() { return m_status; }
		inline int get_buff_len() { return m_buff_len; }

		char* m_data;
		bool m_is_valid;
	private:
		int m_buff_len;

		unsigned int m_delta_time;
		// midi_event:  status, 0x80 - 0xEF
		// meta_event:  0xFF
		// sysex_event: 0xF0
		char m_status;
	};

	class Track
	{
	public:
		Track(char *track_buff);
		~Track();
		bool parse();
		inline unsigned int get_events_count() { return m_events_count; }
		inline unsigned int get_trank_length() { return m_track_chunk->track_length; }

		Event **m_event;
		bool m_is_valid;
	private:
		const int m_mini_event_bytes = 4;
		
		TrackChunk* m_track_chunk;
		unsigned int m_events_count;
		
		void shrinkTrackEventArray();
		bool isValid();
	};

	class Midi
	{
	public:
		Midi(char *midi_buff);
		~Midi();
		bool parse();
		inline unsigned int get_track_count() { return m_track_count; }

		HeaderChunk* m_header_chunk;
		Track **m_track;
		bool m_is_valid;
	private:
		unsigned int m_track_count;

		bool isValid();
	};

	Midi *m_midi;
	short m_channels;

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

	inline bool isValid() { return (m_midi == 0 ? false : m_midi->m_is_valid); }
	inline short get_channels() { return m_channels; }
	bool getNotes(NoteSeries* notes, int channel);

};

