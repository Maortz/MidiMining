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
		inc_len += m_event[m_events_count]->m_buff_len;
		++m_events_count;
	}
	m_is_valid = true;
	return true;
}

MidiParser::Track::~Track()
{

}

MidiParser::MetaEvent::MetaEvent(char* buff, int &len) : EventI()
{
	memset(m_value, 0, 4);
	//
	short* op = reinterpret_cast<short*>(buff);
	switch (*op)
	{
	case MetaTypes::EOT:
		len = 1;
		break;
	case MetaTypes::Key_Sign:
		len = 1 + 2;
		memcpy(m_value, buff + 2, 2);
		break;
	case MetaTypes::Tempo:
		len = 1 + 3;
		memcpy(m_value, buff + 2, 3);
		break;
	case MetaTypes::Time_Sign:
		len = 1 + 4;
		memcpy(m_value, buff + 2, 4);
		break;
	default:
		// Just valid
		if ((buff[0] >= 0x00 && buff[0] <= 0x08) || buff[0] == 0x20 || buff[0] == 0x54 || buff[0] == 0x7F)
		{
			int read_bytes = 0;
			int ev_len = Event::calcLength(buff + 1, read_bytes);
			len = read_bytes + ev_len;
		}
		else
			return;
	}
	m_is_valid = true;
}

MidiParser::SysexEvent::SysexEvent(char *buff, int &len) : EventI()
{
	int read_len = 0;
	int ev_len = Event::calcLength(buff, read_len);
	len = read_len + ev_len;
	m_is_valid = true;
}

MidiParser::MidiEvent::MidiEvent(char *buff, char status, int &len) : EventI()
{
	m_channel = 0x1 << ((status & 0x0F) - 1);
	// Note's channels
	if (status >= 0x90 && status <= 0x9F)
	{
		m_type = Event2Type::Note_Event;
		len = 2;
		m_details = new NoteEvent(buff[0], buff[1]);
	}
	// Control
	else if (status >= 0xB0 && status <= 0xBF)
	{
		m_type = Event2Type::Symbol_Event;
		m_details = new SymbolsEvent(buff[0], buff[1], len);
	}
	// Program
	else if (status >= 0xC0 && status <= 0xCF)
	{
		m_type = Event2Type::Program_Event;
		len = 1;
		m_details = new ProgramEvent(buff[0]);
	}
	else
	{
		// Calc len:
		// For 2 bytes
		if ((status >= 0x80 && status <= 0xAF) || status >= 0xE0 && status <= 0xEF)
			len = 2;
		// For 1 byte
		else if (status >= 0xC0 && status <= 0xDF)
			len = 1;
		else
			return;
		m_is_valid = true;
		return;
	}
	if (!m_details->m_is_valid)
	{
		delete m_details;
		return;
	}
	m_is_valid = true;
}

MidiParser::SymbolsEvent::SymbolsEvent(char symbol, char value, int &len) : EventI2()
{
	switch (symbol)
	{
	case Symbol::Damper_Pedal:
	case Symbol::Legato:
	case Symbol::Portamento:
	case Symbol::Soft_Pedal:
	case Symbol::Sostenuto:
		m_value = value;
		memcpy(&m_symbol, &value, 1);
		m_is_valid = true;
		return;
	default:
		// Calc len:
		// For 2 bytes
		if ((symbol >= 0x00 && symbol <= 0x54) || symbol == 0x58|| symbol >= 0x5B && symbol <= 0x65)
			len = 2;
		// For 1 byte
		else if ((symbol >= 0x55 && symbol <= 0x5A) || (symbol >= 0x66 && symbol <= 0x77))
			len = 1;
		m_symbol = Symbol::None;
		return;
	}
}

MidiParser::Event::Event(char *event_buff)
{
	m_is_valid = false;
	//
	char *buff = event_buff;
	int delta_time_len = 0, event_len = 0;
	m_delta_time = calcLength(buff, delta_time_len);
	buff += delta_time_len;
	set_status(buff[0]);
	buff += 1;
	switch (m_status)
	{
	case EventType::Meta_Event:
		m_type = EventType::Meta_Event;
		m_event_details = new MetaEvent(buff, event_len);
		break;
	case EventType::Sysex_Event1:
	case EventType::Sysex_Event2:
		m_type = EventType::Sysex_Event1;
		m_event_details = new SysexEvent(buff, event_len);
		break;
	default:
		if (m_status > 0xEF || m_status < 0x80)
			return;
		m_type = EventType::Midi_Event;
		m_event_details = new MidiEvent(buff, m_status, event_len);
		break;
	}
	if (!m_event_details->m_is_valid)
	{
		delete m_event_details;
		return;
	}
	m_buff_len = event_len + 1 + delta_time_len;
	m_is_valid = true;
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
