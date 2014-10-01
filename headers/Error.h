// Error class

class Error{
	public:
		std::string short_msg;
		std::string long_msg;
		
	public:
		Error();
		Error(const char* sm, const char* lm);
		operator bool();
		friend std::ostream& operator<<(std::ostream& out, const Error& e);// Overloaded operator to output to ostreams (like std::cout)
		friend bool operator==(Error e1, Error e2);
};

// const Error objects for common Errors

const Error OK("OK", "No error.");
const Error BAD_VOLUME("Bad Volume", "Invalid volume value.");
const Error NOT_MPD_CONNECTION("Not MPD Connection", "The host responded on the port, but the response was not recognized as MPD");
const Error BAD_MPD_VERSION("Bad MPD Version", "The version provided by MPD could not be properly parsed.");
const Error LOCK_FAILURE("Lock Failure", "The connection could not be locked.");
