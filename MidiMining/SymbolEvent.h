
#include "MidiEvent.h"

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
