
class NoteSeries;
class Track;

struct HeaderChunk
{
	char MThd[4];
	int header_length;
	short format;
	short number_of_tracks;
	short division;
	char* data;
};

class Midi
{
public:
	Midi(char *midi_buff, NoteSeries** notes);
	~Midi();
	bool parse();
	inline unsigned int get_track_count() { return m_track_count; }

	HeaderChunk* m_header_chunk;
	Track **m_track;
	bool m_is_valid;
private:
	unsigned int m_track_count;
	NoteSeries** m_notes;

	bool isValid();
};
