
#include "SysexEvent.h"

SysexEvent::SysexEvent(char *buff, int &len) : EventI()
{
	int read_len = 0;
	int ev_len = Event::calcLength(buff, read_len);
	len = read_len + ev_len;
	m_is_valid = true;
}
