
#include "Event.h"

class NoteSeries;

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
