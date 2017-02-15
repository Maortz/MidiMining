#include "MidiParser.h"
#include <string.h>

MidiParser::MidiParser(char* midi, int len)
{
	m_midi_buff = new char[len];
	memcpy(m_midi_buff, midi, len);
}


MidiParser::~MidiParser()
{
}

MidiParser::Midi::Midi(char *midi_buff)
{
	m_header_chunk = reinterpret_cast<HeaderChunk*>(midi_buff);
	m_is_valid = false;
	if (!isValid())
		return;
	m_track_count = m_header_chunk->number_of_tracks;
	m_track = new Track*[m_track_count];
	parse();
}

MidiParser::Midi::~Midi()
{

}

MidiParser::Track::Track(char *track_buff)
{
	m_track_chunk = reinterpret_cast<TrackChunk*>(track_buff);
	m_is_valid = false;
	if (!isValid())
		return;
	int max_events_posibile = m_track_chunk->track_length / m_mini_event_bytes;
	m_event = new Event*[max_events_posibile];
	if (parse())
		shrinkTrackEventArray();
}

bool MidiParser::Track::parse()
{
	m_is_valid = false;
	int inc_len = 0;
	m_events_count = 0;
	while (inc_len < m_track_chunk->track_length)
	{
		m_event[m_events_count] = new Event(m_track_chunk->data + inc_len);
		if (!m_event[m_events_count]->m_is_valid)
		{
			for (size_t j = 0; j <= m_events_count; j++)
				delete m_event[j];
			delete[] m_event;
			return false;
		}
		inc_len += m_event[m_events_count]->get_buff_len();
		++m_events_count;
	}
	m_is_valid = true;
	return true;
}

MidiParser::Track::~Track()
{

}

MidiParser::Event::Event(char *event_buff)
{
	
}

MidiParser::Event::~Event()
{

}

bool MidiParser::Midi::parse()
{
	m_is_valid = false;
	int inc_len = 0;
	for (size_t i = 0; i < get_track_count(); i++)
	{
		m_track[i] = new Track(m_header_chunk->data + inc_len);
		if (!m_track[i]->m_is_valid)
		{
			for (size_t j = 0; j <= i; j++)
				delete m_track[j];
			delete[] m_track;
			return false;
		}
		inc_len += 8 + m_track[i]->get_trank_length();
	}
	m_is_valid = true;
	return true;
}

bool MidiParser::getNotes(NoteSeries* notes, int channel)
{

}