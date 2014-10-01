#include "mpdmm.h"

// Error class

namespace Mpd{

Error::Error():
	short_msg(""),
	long_msg("")
{
	
}

Error::Error(const char* sm, const char* lm) :
	short_msg(sm),
	long_msg(lm)
{
	
}

Error::operator bool(){
	if(short_msg=="OK") return true;
	else return false;
}

std::ostream& operator<<(std::ostream& out, Error e){
	return out << e.long_msg << std::endl << e.short_msg << std::endl;
}

bool operator== (Error e1, Error e2){
	return (e1.short_msg==e2.short_msg && e1.long_msg == e2.long_msg); 
}

}
