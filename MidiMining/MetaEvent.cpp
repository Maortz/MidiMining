
#include "MetaEvent.h"
#include <string>

MetaEvent::MetaEvent(char* buff, int &len) : EventI()
{
	memset(m_value, 0, 4);
	//
	short* op = reinterpret_cast<short*>(buff);
	switch (*op)
	{
	case MetaTypes::EOT:
		len = 1;
		break;
	case MetaTypes::Key_Sign:
		len = 1 + 2;
		memcpy(m_value, buff + 2, 2);
		break;
	case MetaTypes::Tempo:
		len = 1 + 3;
		memcpy(m_value, buff + 2, 3);
		break;
	case MetaTypes::Time_Sign:
		len = 1 + 4;
		memcpy(m_value, buff + 2, 4);
		break;
	default:
		// Just valid
		if ((buff[0] >= 0x00 && buff[0] <= 0x08) || buff[0] == 0x20 || buff[0] == 0x54 || buff[0] == 0x7F)
		{
			int read_bytes = 0;
			int ev_len = Event::calcLength(buff + 1, read_bytes);
			len = read_bytes + ev_len;
		}
		else
			return;
	}
	m_is_valid = true;
}
