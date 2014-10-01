#include "mpdmm.h"

// Status class, represents a snapshot of the mpd status

namespace Mpd {

Status::Status(){

}


std::ostream& operator<<(std::ostream& out, const Status& s){ // Overloaded operator to output to ostreams (like std::cout)
	out << "Volume: " << s.volume << std::endl
		<< "Repeat: " << s.repeat << std::endl
		<< "Random: " << s.random << std::endl
		<< "Single: " << s.single << std::endl
		<< "Consume: " << s.consume << std::endl
		<< "Playlist Revision: " << s.playlist_revision << std::endl
		<< "Playlist Length: " << s.playlist_length << std::endl // Number of songs in playlist
		<< "Crossfade: " << s.crossfade << std::endl
		<< "Mix Ramp On: " << s.mix_ramp_on << std::endl
		<< "Mix Ramp dB: " << s.mix_ramp_db << std::endl // idfk
		<< "Mix Ramp Delay: " << s.mix_ramp_delay << std::endl // ???
		<< "State: " << s.state << std::endl
		<< "Current Song's Number in Playlist: " << s.song_pos << std::endl // song number in playlist, changes when playlist changes
		<< "Current Song's ID in Playlist: " << s.song_id << std::endl // in playlist, does not always change when playlist changes
		<< "Current Song's Length: " << s.song_length << std::endl
		<< "Current Song Elapsed: " << s.song_elapsed << std::endl
		<< "Bitrate: " << s.bitrate << std::endl
		<< "Sample Rate: " << s.sample_rate << std::endl
		<< "Audio Bits: " << s.audio_bits << std::endl // huh?
		<< "Channels: " << s.channels << std::endl
		<< "Update In Progress: " << s.update_in_progress << std::endl
		// error
		<< "Next Song in Playlist's Num: " << s.next_song << std::endl
		<< "Next Song in Playlist's ID: " << s.next_song_id << std::endl
		
		//audio_outputs_on
		// current_song
		<< "Status Retrieved at: " << s.refresh_time << std::endl;
	return out;	
}

}