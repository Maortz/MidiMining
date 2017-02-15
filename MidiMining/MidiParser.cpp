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
	// --- Header --- //
	m_header_chunk = reinterpret_cast<HeaderChunk*>(m_midi);
	if (!headerIsValid())
		return Destroy();
	// --- Tracks --- //
	m_track_count = m_header_chunk->number_of_tracks;
	m_track_chunk = new TrackChunk*[m_track_count];
	int inc_len = 0;
	for (size_t i = 0; i < m_track_count; i++)
	{
		m_track_chunk[i] = reinterpret_cast<TrackChunk*>(m_header_chunk->data + inc_len);
		if (!trackIsValid(i))
			return Destroy();
		inc_len += 8 + m_track_chunk[i]->track_length;
	}
	// --- Events --- //
	int max_events_posibile;
	inc_len = 0;
	for (size_t i = 0, j = 0; i < m_track_count; i++)
	{
		max_events_posibile = m_track_chunk[i]->track_length / m_mini_event_bytes;
		m_track_event[i] = new TrackEvent*[max_events_posibile];
		while (inc_len < m_track_chunk[i]->track_length)
		{
			m_track_event[i][j] = new TrackEvent(m_track_chunk[i]->events + inc_len);
			if (!m_track_event[i][j]->isValid())
				return Destroy();
			inc_len += m_track_event[i][j]->get_buff_len();
			++j;
		}

	}
	//
	m_is_valid = true;
	return true;
}

short MidiParser::get_channels()
{
	return m_channels;
}

bool MidiParser::getNotes(NoteSeries* notes, int channel)
{

}

bool MidiParser::isValid()
{
	return m_is_valid;
}