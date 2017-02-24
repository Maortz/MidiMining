
#include "Event.h"

class NoteSeries;

class SysexEvent : public EventI
{
public:
	SysexEvent(char* buff, int &len);
	~SysexEvent();

private:

};
