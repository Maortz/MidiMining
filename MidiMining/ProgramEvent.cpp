
#include "ProgramEvent.h"
#include <string>

ProgramEvent::ProgramEvent(char value)
{
	if (value < 0)
		return;
	m_is_valid = true;
	memcpy(&m_instrument, &value, 1);
	if (m_instrument < Chromatic_Percussion)
		m_instrument_family = Piano;
	else if (m_instrument < Organ)
		m_instrument_family = Chromatic_Percussion;
	else if (m_instrument < Guitar)
		m_instrument_family = Organ;
	else if (m_instrument < Bass)
		m_instrument_family = Guitar;
	else if (m_instrument < Strings)
		m_instrument_family = Bass;
	else if (m_instrument < Ensemble)
		m_instrument_family = Strings;
	else if (m_instrument < Brass)
		m_instrument_family = Ensemble;
	else if (m_instrument < Reed)
		m_instrument_family = Brass;
	else if (m_instrument < Pipe)
		m_instrument_family = Reed;
	else if (m_instrument < Synth_Lead)
		m_instrument_family = Pipe;
	else if (m_instrument < Synth_Pad)
		m_instrument_family = Synth_Lead;
	else if (m_instrument < Synth_Effects)
		m_instrument_family = Synth_Pad;
	else if (m_instrument < Ethnic)
		m_instrument_family = Synth_Effects;
	else if (m_instrument < Percussive)
		m_instrument_family = Ethnic;
	else if (m_instrument < Sound_Effects)
		m_instrument_family = Percussive;
	else
		m_instrument_family = Sound_Effects;
}
