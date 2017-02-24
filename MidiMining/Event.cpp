
#include "Event.h"

#include "MetaEvent.h"
#include "SysexEvent.h"
#include "MidiEvent.h"

Event::Event(char *event_buff, NoteSeries** notes) : m_event_details(0), m_is_valid(false), m_notes(notes)
{
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
		m_event_details = new MidiEvent(buff, m_status, event_len, m_notes);
		break;
	}
	m_buff_len = event_len + 1 + delta_time_len;
	if (!m_event_details->m_is_valid)
	{
		delete m_event_details;
		m_event_details = 0;
		return;
	}
	m_is_valid = true;
}

Event::~Event()
{
	if (!m_event_details)
		delete m_event_details;
}
