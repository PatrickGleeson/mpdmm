#include "mpdmm.h"

// Output Device class

namespace Mpd{

OutputDevice::OutputDevice():
	connection(NULL),
	id(-1),
	name(""),
	enabled(false)
{
	
}

OutputDevice::OutputDevice(Connection* c, int i, const char* n, bool e):
	connection(c),
	id(i),
	name(n),
	enabled(e)
{
	
}

int OutputDevice::get_id(){
	return id;
}

std::string OutputDevice::get_name(){
	return name;
}

bool OutputDevice::get_enabled(){
	return enabled;
}

}