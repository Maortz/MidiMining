#pragma once
class Note
{
	unsigned int m_semitones;
	unsigned int m_duration;
public:
	Note();
	~Note();

	void set_semitones(unsigned int note);
	unsigned int get_semitones();
	void set_duration(unsigned int note);
	unsigned int get_duration();

	static int GetInterval(Note note1, Note note2);
};

