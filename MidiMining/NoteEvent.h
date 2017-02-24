
#include "MidiEvent.h"
#include "Note.h"

class NoteEvent : public EventI2
{
public:
	NoteEvent(char note, char velocity);
	~NoteEvent();

	Note m_note;
private:

};
