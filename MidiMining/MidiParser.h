#pragma once
#include "Note.h"
class NoteSeries;

class MidiParser
{
	char * m_midi_buff;
	struct TrackChunk
	{
		char MTrk[4];
		int track_length;
		char* data;
	};
	struct HeaderChunk
	{
		char MThd[4];
		int header_length;
		short format;
		short number_of_tracks;
		short division;
		char* data;
	};

	class EventI
	{
	public:
		EventI() : m_is_valid(false) {}
		bool m_is_valid;
	};
	class EventI2
	{
	public:
		EventI2() : m_is_valid(false) {}
		bool m_is_valid;
	};

	class NoteEvent : public EventI2
	{
	public:
		NoteEvent(char note, char velocity);
		~NoteEvent();

		Note m_note;
	private:

	};

	enum InstrumentFamiles
	{
		Piano = 1,
		Chromatic_Percussion = 9,
		Organ = 17,
		Guitar = 25,
		Bass = 33,
		Strings = 41,
		Ensemble = 49,
		Brass = 57,
		Reed = 65,
		Pipe = 73,
		Synth_Lead = 81,
		Synth_Pad = 89,
		Synth_Effects = 97,
		Ethnic = 105,
		Percussive = 113,
		Sound_Effects = 121
	};

	enum Instruments
	{
		Acoustic_Grand_Piano = 1,
		Bright_Acoustic_Piano,
		Electric_Grand_Piano,
		Honky_tonk_Piano,
		Electric_Piano_1_Rhodes_Piano,
		Electric_Piano_2_Chorused_Piano,
		Harpsichord,
		Clavinet,
		Celesta,
		Glockenspiel,
		Music_Box,
		Vibraphone,
		Marimba,
		Xylophone,
		Tubular_Bells,
		Dulcimer_Santur,
		Drawbar_Organ_Hammond,
		Percussive_Organ,
		Rock_Organ,
		Church_Organ,
		Reed_Organ,
		Accordion_French,
		Harmonica,
		Tango_Accordion_Band_neon,
		Acoustic_Guitar_nylon,
		Acoustic_Guitar_steel,
		Electric_Guitar_jazz,
		Electric_Guitar_clean,
		Electric_Guitar_muted,
		Overdriven_Guitar,
		Distortion_Guitar,
		Guitar_harmonics,
		Acoustic_Bass,
		Electric_Bass_fingered,
		Electric_Bass_picked,
		Fretless_Bass,
		Slap_Bass_1,
		Slap_Bass_2,
		Synth_Bass_1,
		Synth_Bass_2,
		Violin,
		Viola,
		Cello,
		Contrabass,
		Tremolo_Strings,
		Pizzicato_Strings,
		Orchestral_Harp,
		Timpani,
		String_Ensemble_1_strings,
		String_Ensemble_2_slow_strings,
		SynthStrings_1,
		SynthStrings_2,
		Choir_Aahs,
		Voice_Oohs,
		Synth_Voice,
		Orchestra_Hit,
		Trumpet,
		Trombone,
		Tuba,
		Muted_Trumpet,
		French_Horn,
		Brass_Section,
		SynthBrass_1,
		SynthBrass_2,
		Soprano_Sax,
		Alto_Sax,
		Tenor_Sax,
		Baritone_Sax,
		Oboe,
		English_Horn,
		Bassoon,
		Clarinet,
		Piccolo,
		Flute,
		Recorder,
		Pan_Flute,
		Blown_Bottle,
		Shakuhachi,
		Whistle,
		Ocarina,
		Lead_1_square_wave,
		Lead_2_sawtooth_wave,
		Lead_3_calliope,
		Lead_4_chiffer,
		Lead_5_charang,
		Lead_6_voice_solo,
		Lead_7_fifths,
		Lead_8_bass_lead,
		Pad_1_new_age_Fantasia,
		Pad_2_warm,
		Pad_3_polysynth,
		Pad_4_choir_space_voice,
		Pad_5_bowed_glass,
		Pad_6_metallic_pro,
		Pad_7_halo,
		Pad_8_sweep,
		FX_1_rain,
		FX_2_soundtrack,
		FX_3_crystal,
		FX_4_atmosphere,
		FX_5_brightness,
		FX_6_goblins,
		FX_7_echoes_drops,
		FX_8_sci_fi_star_theme,
		Sitar,
		Banjo,
		Shamisen,
		Koto,
		Kalimba,
		Bag_pipe,
		Fiddle,
		Shanai,
		Tinkle_Bell,
		Agogo,
		Steel_Drums,
		Woodblock,
		Taiko_Drum,
		Melodic_Tom,
		Synth_Drum,
		Reverse_Cymbal,
		Guitar_Fret_Noise,
		Breath_Noise,
		Seashore,
		Bird_Tweet,
		Telephone_Ring,
		Helicopter,
		Applause,
		Gunshot
	};

	class ProgramEvent : public EventI2
	{
	public:
		ProgramEvent(char value);
		~ProgramEvent();

		Instruments m_instrument;
		InstrumentFamiles m_instrument_family;
	private:

	};

	enum Symbol
	{
		None,
		Damper_Pedal = 0x40,
		Portamento,
		Sostenuto,
		Soft_Pedal,
		Legato
	};

	class SymbolsEvent : public EventI2
	{
	public:
		SymbolsEvent(char symbol, char value, int &len);
		~SymbolsEvent();

		Symbol m_symbol;
		char m_value;
	private:

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
		MidiEvent(char* buff, char status, int &len);
		~MidiEvent();

		short m_channel;
		EventI2* m_details;
		Event2Type m_type;
	private:

	};

	enum MetaTypes
	{
		EOT = 0x2F00,
		Tempo = 0x5103,
		Time_Sign = 0x5804,
		Key_Sign = 0x5902
	};

	class MetaEvent : public EventI
	{
	public:
		MetaEvent(char* buff, int &len);
		~MetaEvent();

		MetaTypes m_type;
		char m_value[4];

	private:

	};

	class SysexEvent : public EventI
	{
	public:
		SysexEvent(char* buff, int &len);
		~SysexEvent();

	private:

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
		Event(char* event_buff);
		~Event();
		bool parse();
		static int calcLength(char* time_buff, int &read_bytes);
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
	};

	class Track
	{
	public:
		Track(char *track_buff);
		~Track();
		bool parse();
		inline unsigned int get_events_count() { return m_events_count; }
		inline unsigned int get_trank_length() { return m_track_chunk->track_length; }

		Event **m_event;
		bool m_is_valid;
	private:
		const int m_mini_event_bytes = 4;
		
		TrackChunk* m_track_chunk;
		unsigned int m_events_count;
		
		void shrinkTrackEventArray();
		bool isValid();
	};

	class Midi
	{
	public:
		Midi(char *midi_buff);
		~Midi();
		bool parse();
		inline unsigned int get_track_count() { return m_track_count; }

		HeaderChunk* m_header_chunk;
		Track **m_track;
		bool m_is_valid;
	private:
		unsigned int m_track_count;

		bool isValid();
	};

	Midi *m_midi;
	short m_channels;

public:

	const char c_short_bits[] = {
		0x0001,
		0x0002,
		0x0004,
		0x0008,
		0x0010,
		0x0020,
		0x0040,
		0x0080,
		0x0100,
		0x0200,
		0x0400,
		0x0800,
		0x1000,
		0x2000,
		0x4000,
		0x8000
	};

	MidiParser(char* midi, int len);
	~MidiParser();

	inline bool isValid() { return (m_midi == 0 ? false : m_midi->m_is_valid); }
	inline short get_channels() { return m_channels; }
	bool getNotes(NoteSeries* notes, int channel);

};

