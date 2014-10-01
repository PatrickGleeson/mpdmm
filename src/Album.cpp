#include "mpdmm.h"

// Album class

namespace Mpd{

Album::Album(Connection* c, const char* n, bool load){
	connection = c;
	name = n;
	if(load) load_all();
}

const char* Album::get_name() const{
	return name.c_str();
}

std::vector<Artist*> Album::get_artists(){
	if(artists.empty()) load_artists();
	return artists;
}

std::vector<Song*> Album::get_songs(){
	if(songs.empty()) load_songs();
	return songs;
}

void Album::load_artists(){
	
}

void Album::load_songs(){
	
}

void Album::load_all(){
	load_artists();
	load_songs();
}

std::ostream& operator<<(std::ostream& out, const Album& a){ // Overloaded operator to output to ostreams (like std::cout)
	out << "Album Name: " << a.name << std::endl;
	int i;
	for(i=0;i<a.artists.size();i++) out << "Artist: " << a.artists[i]->get_name() << std::endl;
	for(i=0;i<a.songs.size();i++) out << "Songs: " << a.songs[i]->name << std::endl;
	
	return out;
}

}