#include "mpdmm.h"


int main(){
	// Main for testing things
	Mpd::Connection default_connection;
	std::cout << "Default connection created." << std::endl;
	
	Mpd::Error e = default_connection.connect();
	std::cout << "mpdmm error:" <<  e.short_msg << std::endl;
	std::cout << "Connect() done." << std::endl;
	
	std::string tmp;
	
	std::vector<Mpd::Artist> artists;
	artists = default_connection.get_artists();
	std::cout << "Size of artists vector: " << artists.size() << std::endl;
	for(int i=0;i<artists.size();i++) std::cout << artists[i];
	std::cin >> tmp;
	//std::cout << "get_status() attempted." << std::endl;
	//std::cout << s;
	
	

	e = default_connection.flip_random();
	if(!e) std::cout << e.short_msg << std::endl;
	std::cout << "flip_random() attempted." << std::endl;
	std::cin >> tmp;
	
/*	e = default_connection.prev();
	if(!e) std::cout << e.short_msg << std::endl;
	std::cout << "prev() attempted." << std::endl;
	std::cin >> tmp;
	
	e = default_connection.previous();
	if(!e) std::cout << e.short_msg << std::endl;
	std::cout << "previous() attempted." << std::endl;
	*/
	return true;
}
