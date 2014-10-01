// Output Device class

class OutputDevice{
	private:
		Connection* connection;
		int id;
		std::string name;
		bool enabled;
		
	public:
		OutputDevice();
		OutputDevice(Connection* c, int i, const char* n, bool e);
		int get_id();
		std::string get_name();
		bool get_enabled();
		friend std::ostream& operator<<(std::ostream& out, const OutputDevice& od); // Overloaded operator to output to ostreams (like std::cout)
};