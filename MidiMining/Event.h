
class NoteSeries;

class EventI
{
public:
	EventI() : m_is_valid(false) {}
	bool m_is_valid;
};

enum EventType
{
	Meta_Event = 0xFF,
	Sysex_Event1 = 0xF0,
	Sysex_Event2 = 0xF7,
	Midi_Event
};

class Event
{
public:
	Event(char* event_buff, NoteSeries** notes);
	~Event();
	bool parse();
	// TODO: impl
	static int calcLength(char* time_buff, int &read_bytes);
	// TODO: impl
	void set_status(char status);

	bool m_is_valid;
	int m_buff_len;

	unsigned int m_delta_time;
	// midi_event:  status, 0x80 - 0xEF
	// meta_event:  0xFF
	// sysex_event: 0xF0
	char m_status;

	EventI* m_event_details;
	EventType m_type;

private:
	NoteSeries** m_notes;
};
