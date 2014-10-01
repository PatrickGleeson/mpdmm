// Song class

class Song : public FileSystemEntry{
	public:
		// timestamp last_modified;
		int length; // In seconds
		std::string title; // title of a track
		int track;
		std::string name; // name of an audio stream
		std::string genre; // Can this be multiple?
		int year;
		std::string composer;
		std::string performer;
		std::string comment;
		int disc;
		//Artist artist;
		//Album album;
		
	public:
		Song();
		Song(
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
			const Artist* ar=NULL,
			const Album* al=NULL
		);
		friend std::ostream& operator<<(std::ostream& out, const Song& s); // Overloaded operator to output to ostreams (like std::cout)
};

