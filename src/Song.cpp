#include "mpdmm.h"

// Song class

namespace Mpd{

Song::Song():
	length(0),
	title(""),
	track(0),
	name(""),
	genre(""),
	year(0),
	composer(""),
	performer(""),
	comment(""),
	disc(0)
	//artist = *ar;
	//album = *al;
{

}

Song::Song(
	Connection* conn,
	const char* pa,
	//timestamp lm,
	int l,
	const char* ti,
	int tr,
	const char* n,
	const char* g,
	int y,
	const char* comp,
	const char* pe,
	const char* comm,
	int d,
	const Artist* ar,
	const Album* al
):
	//last_modified(lm),
	length(l),
	title(ti),
	track(tr),
	name(n),
	genre(g),
	year(y),
	composer(comp),
	performer(pe),
	comment(comm),
	disc(d)
	//artist = *ar;
	//album = *al;
	
{
	FileSystemEntry(conn,pa);
}

}