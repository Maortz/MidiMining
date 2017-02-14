#pragma once
class Note
{
public:

	unsigned int m_semitones;
	unsigned int m_duration;
	double m_bar_position;
	double m_start_position;

	Note();
	~Note();

	double endBarPosition();
	double endstartPosition();
	
	static int getInterval(Note note1, Note note2);

};

