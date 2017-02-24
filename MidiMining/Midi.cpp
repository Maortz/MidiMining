
#include "Midi.h"
#include "Track.h"

Midi::Midi(char *midi_buff, NoteSeries** notes)
{
	m_header_chunk = reinterpret_cast<HeaderChunk*>(midi_buff);
	m_is_valid = false;
	if (!isValid())
		return;
	m_notes = notes;
	m_track_count = m_header_chunk->number_of_tracks;
	m_track = new Track*[m_track_count];
	parse();
}

Midi::~Midi()
{
	int count = get_track_count();
	for (size_t i = 0; i < count; i++)
		if (!m_track[i])
			delete m_track[i];
	delete m_track;
}

bool Midi::parse()
{
	m_is_valid = false;
	int inc_len = 0;
	int i, j;
	int count = get_track_count();
	for (i = j = 0; i < count; i++)
	{
		m_track[i] = new Track(m_header_chunk->data + inc_len, m_notes);
		if (!m_track[i]->m_is_valid)
		{
			delete m_track[i];
			m_track = 0;
			j++;
		}
		inc_len += 8 + m_track[i]->get_trank_length();
	}
	if (i == j)
		return false;
	m_is_valid = true;
	return true;
}
