
#include "SymbolEvent.h"
#include <string>

SymbolsEvent::SymbolsEvent(char symbol, char value, int &len) : EventI2()
{
	switch (symbol)
	{
	case Symbol::Damper_Pedal:
	case Symbol::Legato:
	case Symbol::Portamento:
	case Symbol::Soft_Pedal:
	case Symbol::Sostenuto:
		m_value = value;
		memcpy(&m_symbol, &symbol, 1);
		m_is_valid = true;
		return;
	default:
		// Calc len:
		// For 2 bytes
		if ((symbol >= 0x00 && symbol <= 0x54) || symbol == 0x58 || symbol >= 0x5B && symbol <= 0x65)
			len = 2;
		// For 1 byte
		else if ((symbol >= 0x55 && symbol <= 0x5A) || (symbol >= 0x66 && symbol <= 0x77))
			len = 1;
		m_symbol = Symbol::None;
		return;
	}
}
