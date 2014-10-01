// Connection class


class Connection{
	public:
		bool connected;
		std::string hostname;
		int port;
		std::string password;
		float timeout;
		
		Network::TcpSocket socket;		
		
		struct{
			int major;
			int minor;
			int micro;
		} version;
		
		bool lock_flag;
		
		Song currentSong;
		float elapsedSong;
		
		Status status;
		
		Stats stats;
		
		std::vector<Artist> artists;
		std::vector<Album> albums;
		std::vector<Song> songs;
		std::vector<OutputDevice> output_devices;
		std::vector<std::string> url_handlers;
		std::vector<std::string> tag_types;
		
		bool has_idle;
	
		bool lock();
		void unlock();
		 
	public:
	//libmpd-player
		Error play();
		Error play_num(int songNum);
		Error play_id(int songID);
		Error stop();
		Error next();
		Error prev();
		Error previous();
		Error pause();
		Error unpause();
		Error set_pause(bool p);
		Error flip_pause();
		Status get_status();
		int get_current_song_id();
		int get_current_song_position(); // in playlist
		bool get_repeat();
		Error set_repeat(bool r);
		Error flip_repeat();
		bool get_random();
		Error set_random(bool r);
		Error flip_random();
		Error seek(int seconds); // To a certain time in the song
		Error seek_in_song_pos(int song_pos, int seconds);
		Error seek_in_song_id(int song_id, int seconds);
		
	//libmpd-status
		bool status_check(); // if there's a new status [internal]
		void queue_update(); // mark the current status invalid
		Error refresh_status(); // get new status
		// Also do something to support a status fetching loop with all other operation being interrupt based
		Error set_volume(int vol); // 0-100
		Error set_volume(double vol); // 0-1
		Error set_crossfade(int seconds);
		bool is_db_updating(); // T/F
		std::string get_mpd_error(); // get mpd error message
		Error refresh_stats(); //[internal]
		Stats get_stats();
			
	//libmpd-database	
		std::vector<Album> parse_albums(std::vector<std::string> ret);
		std::vector<Album> get_albums(Artist artist); // get all albums of artist (or if no artist, all albums)
		std::vector<Album> get_albums(const char* artist);
		std::vector<Album> get_albums(); // All
		std::vector<Artist> get_artists();
		std::vector<Artist> get_album_artists(const char* album);
		std::vector<Song> parse_songs(std::vector<std::string> ret);
		std::vector<Song> get_songs_with_tag(const char* type, const char* match);
		std::vector<Song> get_artist_songs(const char* album);
		std::vector<Song> get_album_songs(const char* album);
		std::vector<Song> get_all_songs(); // Every song
		Error update_dir(const char* dir); // "update (parts of) the database" whut?
		// find() // depreciated
		std::vector<FileSystemEntry> get_directory(const char* directory_path); //returns songs, directories and playlists (I think all of those are files)
		std::vector<FileSystemEntry> get_directory_recursive(const char* directory_path); // like the above
		Song get_fileinfo(const char* file_path);
		/* Searching needs an overhaul, below is current scheme
			search_start() // bool for "exact" w/e that means
			search_add_constraint() // passed a type of tag and a value for said tag
			search_field_start() what to search for (I think)
			search_commit() // do the search
			// Some other stuff for the stats on a search result
		*/
		
		/* Spin this off into it's own object
		bool delete_playlist(const char* file_path);
		bool save_playlist(const char* file_path) // Saves current
		std::vector<Song> get_playlist_content();
		bool playlist_list_add() // Adds a file path to a playlist
		playlist_list_delete(pos) // Delete entry at pos
		playlist_clear()
		playlist_rename()
		playlist_list_move() move an entry
		playlist_list() // get whats on the playlist
		
		*/
		
	//libmpd-playlist
		/* possibly with the above
		get_playlist_id() // of current playlist
		get_old_playlist_id()
		playlist_get_song(songid) // not qute sure
		playlist_get_song_from_pos()
		playlist_get_song_from_pos_range()
		playlist_get_current_song()
		playlist_clear()
		playlist_shuffle() // actually shuffle the playlist, not just switch to random
		playlist_move_pos()
		playlist_move_id()
		playlist_get_changes()
		playlist_get_changes_posid()
		get_playist_length()
		
		playlist_add()
		playlist_delete_id()
		playlist_delete_pos()
		playlist_add_get_id()
		
		bool playlist_queue_add();
		playlist_queue_load() // playlist
		playlist_queue_delete_id()
		playlist_queue_delete_pos()
		playlist_queue_commit()
		*/
		// Playlist searching
		
		Error queue_add(const Song* s); // add to current queue
		Error queue_remove(const Song* s); // remove from current queue
		
	//libmpd
 		Connection(const char* hn="localhost", int pt=6600, const char* pw="", float to=1);
		void set_hostname(const char* hn);
		const char* get_hostname();
		void set_password(const char* pw);
		// get_password() Hmmm
		void set_connection_timeout(float seconds);
		int get_connection_timeout();
		Error connect();
		Error disconnect();
		bool check_connected();
		Error check_error();
		~Connection();
		Error send_password(); // re-auth
		std::vector<OutputDevice> get_output_devices();
		Error set_output_device(OutputDevice od, bool e);
		Error enable_output_device(OutputDevice od);
		Error disable_output_device(OutputDevice od);
		Error flip_output_device(OutputDevice od);
		Error set_output_device(int od_id, bool e);		
		Error enable_output_device(int od_id);
		Error disable_output_device(int od_id);
		Error flip_output_device(int od_id);
		int get_database_update_time(); // last time database updated
		bool check_version(int major, int minor, int micro);
		const char* get_version();
		//check_command_allowed()
		std::vector<std::string> get_url_handlers();
		std::vector<std::string> get_tag_types();
		//get_tag_by_name() // probably don't need this
		bool server_has_idle();
		bool is_tag_supported(const char* t);
		void start_execute(const char* command);
		void finish_execute();
		std::vector<std::string> execute_and_return(const char* command);
		Error execute_or_error(const char* command);
	
	//libmpdclient
		// include most elements from mpd_connection, mpd_status, mpd_stats
		Error refresh_allowed_commands();
		Error refresh_current_stats();
		Error refresh_current_song();
		Error refresh_playlist_info(); // Differnce?
		Error refresh_playlist_id(); // ^
		// get_changes_since_playlist(playlist)
		
	// Needs single mode, start db update, consume mode, mix ramping	
	
};
