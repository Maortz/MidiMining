

class NoteSeries;
class Event;

struct TrackChunk
{
	char MTrk[4];
	int track_length;
	char* data;
};

class Track
{
public:
	Track(char *track_buff, NoteSeries** notes);
	~Track();
	bool parse();
	inline unsigned int get_events_count() { return m_events_count; }
	inline unsigned int get_trank_length() { return m_track_chunk->track_length; }

	Event **m_event;
	bool m_is_valid;
private:
	const int m_mini_event_bytes = 4;
	NoteSeries** m_notes;

	TrackChunk* m_track_chunk;
	unsigned int m_events_count;

	// TODO: impl
	void shrinkTrackEventArray();
	// TODO: impl
	bool isValid();
};
