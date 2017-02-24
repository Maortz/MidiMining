
#include "Event.h"

class NoteSeries;

class EventI2
{
public:
	EventI2() : m_is_valid(false) {}
	bool m_is_valid;
};


enum Event2Type
{
	Note_Event,
	Program_Event,
	Symbol_Event
};

class MidiEvent : public EventI
{
public:
	MidiEvent(char* buff, char status, int &len, NoteSeries** notes);
	~MidiEvent();

	short m_channel;
	EventI2* m_details;
	Event2Type m_type;
private:
	NoteSeries** m_notes;
};
