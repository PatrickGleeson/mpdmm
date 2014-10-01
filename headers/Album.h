// Album class

class Album {
private:
	Connection* connection;
	std::string name;
	std::vector<Artist*> artists; // An album may have songs by more then one artist, especially compilation discs
	std::vector<Song*> songs;
	
public:
	Album();
	Album(Connection* c, const char* n, bool load=false);
	const char* get_name() const;
	std::vector<Artist*> get_artists();
	std::vector<Song*> get_songs();
	void load_songs();
	void load_artists();
	void load_all();
	friend std::ostream& operator<<(std::ostream& out, const Album& a); // Overloaded operator to output to ostreams (like std::cout)
	
};