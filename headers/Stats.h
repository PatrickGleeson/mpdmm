// Stats class, represents a snapshot of the mpd stats

class Stats {
	public:
		int artists;
		int albums;
		int songs;
		int uptime;
		int time_playing;
		int total_db_playtime;
		int last_db_update;
		int refresh_time;
		Stats();
		friend std::ostream& operator<<(std::ostream& out, const Stats& s); // Overloaded operator to output to ostreams (like std::cout)
};