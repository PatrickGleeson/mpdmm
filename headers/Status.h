// Status class, represents a snapshot of the mpd status

class Status {
	public:
		int volume;
		bool repeat;
		bool random;
		bool single;
		bool consume;
		uint playlist_revision;
		int playlist_length; // Number of songs in playlist
		int crossfade;
		bool mix_ramp_on;
		int mix_ramp_db; // idfk
		int mix_ramp_delay; // ???
		std::string state;
		int song_pos; // song position in playlist, changes when playlist changes
		int song_id; // in playlist, does not always change when playlist changes
		int song_length;
		float song_elapsed;
		int bitrate;
		int sample_rate;
		int audio_bits; // huh?
		int channels;
		bool update_in_progress;
		// string error; // Not sure if needed
		int next_song;
		int next_song_id;
		
		/* Possible additions:
		audio_outputs_on
		Song current_song
		
		*/
		int refresh_time;		
		
		Status();
		friend std::ostream& operator<<(std::ostream& out, const Status& s); // Overloaded operator to output to ostreams (like std::cout)
		
};

