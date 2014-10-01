#include "mpdmm.h"

// File class, a base class for song, playlist and directory

namespace Mpd{

FileSystemEntry::FileSystemEntry(){
	connection = NULL;
	path = "";
}

FileSystemEntry::FileSystemEntry(Connection* c, const char* p){
	connection = c;
	path=p;
}

}