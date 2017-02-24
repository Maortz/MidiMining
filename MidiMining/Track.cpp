
#include "Track.h"
#include "Event.h"

Track::Track(char *track_buff, NoteSeries** notes)
{
	m_track_chunk = reinterpret_cast<TrackChunk*>(track_buff);
	m_is_valid = false;
	if (!isValid())
		return;
	m_notes = notes;
	int max_events_posibile = m_track_chunk->track_length / m_mini_event_bytes;
	m_event = new Event*[max_events_posibile];
	if (parse())
		shrinkTrackEventArray();
}

bool Track::parse()
{
	m_is_valid = false;
	int inc_len = 0;
	m_events_count = 0;
	while (inc_len < m_track_chunk->track_length)
	{
		m_event[m_events_count] = new Event(m_track_chunk->data + inc_len, m_notes);
		inc_len += m_event[m_events_count]->m_buff_len;
		if (!m_event[m_events_count]->m_is_valid)
			delete m_event[m_events_count];
		else
			++m_events_count;
	}
	if (m_events_count == 0)
		return false;
	m_is_valid = true;
	return true;
}

Track::~Track()
{
	for (size_t i = 0; i < m_events_count; i++)
		delete m_event[i];
	delete[] m_event;
}
