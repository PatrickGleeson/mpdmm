// File class, a base class for song, playlist and directory

class FileSystemEntry{
	private:
		Connection* connection;
		std::string path;
	
	public:
		FileSystemEntry();
		FileSystemEntry(Connection* c, const char* p);
		friend std::ostream& operator<<(std::ostream& out, const FileSystemEntry& fse); // Overloaded operator to output to ostreams (like std::cout)
};