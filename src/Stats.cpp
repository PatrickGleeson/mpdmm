#include "mpdmm.h"

// Stats class, represents a snapshot of the mpd stats

namespace Mpd {

Stats::Stats(){

}

std::ostream& operator<<(std::ostream& out, const Stats& s){ // Overloaded operator to output to ostreams (like std::cout)
	out << "Number of Artists: " << s.artists << std::endl
		<< "Number of Albums: " << s.albums << std::endl
		<< "Number of Songs: " << s.songs << std::endl
		<< "Uptime: " << s.uptime << std::endl
		<< "Time Playing: " << s.time_playing << std::endl
		<< "Total Playtime of All Songs in Database: " << s.total_db_playtime << std::endl
		<< "Time of Last Database Update: "<< s.last_db_update << std::endl
		<< "Stats Retrieved at: " << s.refresh_time << std::endl;
	return out;
}

}