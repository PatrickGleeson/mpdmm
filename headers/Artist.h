// Artist class

class Artist {
public:
	Connection* connection;
	std::string name;
	std::vector<Album*> albums;
	std::vector<Song*> songs;
	
public:
	Artist();
	Artist(Connection* c, const char* n, bool load=false);
	std::string get_name() const;
	std::vector<Album*> get_albums();
	std::vector<Song*> get_songs();
	friend std::ostream& operator<<(std::ostream& out, const Artist& a); // Overloaded operator to output to ostreams (like std::cout)
	
};