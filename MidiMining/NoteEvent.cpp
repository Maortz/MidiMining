
#include "NoteEvent.h"

NoteEvent::NoteEvent(char note, char velocity)
{
	m_note.m_semitones = note;
	m_note.m_duration = Note::ppqnToDuration()
		m_is_valid = true;
}
