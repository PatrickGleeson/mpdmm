#include "mpdmm.h"

// Artist class

namespace Mpd{

Artist::Artist(Connection* c, const char* n, bool load){
	connection = c;
	name = n;
	//if(load) load_all();
}

std::string Artist::get_name() const{
	return name;
}

std::vector<Album*> Artist::get_albums(){
	return albums;
}

std::vector<Song*> Artist::get_songs(){
	return songs;
}

std::ostream& operator<<(std::ostream& out, const Artist& a){ // Overloaded operator to output to ostreams (like std::cout)
	out << "Artist Name: " << a.name << std::endl;
	int i;
	for(i=0;i<a.albums.size();i++) out << "Album: " << a.albums[i]->get_name() << std::endl;
	for(i=0;i<a.songs.size();i++) out << "Song: " << a.songs[i]->name << std::endl;
}

}
