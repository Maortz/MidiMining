#pragma once
class Note
{
public:

	unsigned int m_semitones;
	double m_duration;
	double m_bar_position;
	double m_start_position;

	Note();
	~Note();

	double endBarPosition();
	double endStartPosition();
	/*
	Gets: Allocated with 3 chars (last for \0, "A#\0")
	*/
	void noteSign(char* buff);
	int octaveFromMiddle();

	static int getInterval(Note &note1, Note &note2);
	static double ppqnToDuration(unsigned int division, unsigned int ppqn);
};

