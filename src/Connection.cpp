#include "mpdmm.h"

namespace Mpd {

bool Connection::lock(){
	if(lock_flag==true) return false; // If it's already locked, return false to represent an error
	else{
		lock_flag = true;
		return true;
	}
}

void Connection::unlock(){
	lock_flag = false;
}

Error Connection::play(){ // Tested
	return execute_or_error("play");
}

Error Connection::play_num(int songNum){ // Tested
	std::stringstream command;
	command << "play " << songNum;
	return execute_or_error(command.str().c_str());
}

Error Connection::play_id(int songID){ // Tested
	std::stringstream command;
	command << "playid " << songID;
	return execute_or_error(command.str().c_str());
}

Error Connection::stop(){ // Tested
	return execute_or_error("stop");
}

Error Connection::next(){ // Tested
	return execute_or_error("next");
}

Error Connection::prev(){ // Tested
	return execute_or_error("previous");
}
Error Connection::previous(){ // Tested
	return execute_or_error("previous");
}

Error Connection::pause(){ // Tested
	return execute_or_error("pause 1");
}

Error Connection::unpause(){ // Tested
	return execute_or_error("pause 0");
}

Error Connection::set_pause(bool p){ // Tested
	if(p) return execute_or_error("pause 1");
	else return execute_or_error("pause 0");
}

Error Connection::flip_pause(){ // Tested
	if(status.state=="pause") return unpause();
	if(status.state=="play") return pause();
	if(status.state=="stop") return OK;
}

Status Connection::get_status(){
	//check_safe();
	refresh_status();
	return status;
}

Error Connection::set_repeat(bool r){ // Tested
	if(r) return execute_or_error("repeat 1");
	else return execute_or_error("repeat 0");
}

Error Connection::flip_repeat(){ // Tested
	return set_repeat(!status.repeat);
}

Error Connection::set_random(bool r){ // Tested
	if(r) return execute_or_error("random 1");
	else return execute_or_error("random 0");
}

Error Connection::flip_random(){ // Tested
	return set_random(!status.random);
}
Error Connection::seek(int seconds){ // To a certain time in the current song
	return seek_in_song_pos(status.song_pos, seconds);
} // Tested

Error Connection::seek_in_song_pos(int song_pos, int seconds){
	std::stringstream command;
	command << "seek " << song_pos << " " << seconds;
	return execute_or_error(command.str().c_str());
} // Tested

Error Connection::seek_in_song_id(int song_id, int seconds){
	std::stringstream command;
	command << "seekid " << song_id << " " << seconds;
	return execute_or_error(command.str().c_str());
} // Tested


//libmpd-status
//bool Connection::status_check(); // if there's a new status [internal]

//void Connection::queue-update(); // mark the current status invalid


Error Connection::refresh_status(){ // get new status and respond appropriately
	std::vector<std::string> result;
	result = execute_and_return("status");
	int i=0;
	bool skipped_through = false;
	std::string tmp;
	Error e = OK;
	while(i<result.size()){
		if(i<result.size()) if(result[i].substr(0,8)=="volume: "){
			status.volume=atoi(result[i].substr(8).c_str());
			std::cout << "Volume is: " << status.volume << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="repeat: "){
			status.repeat=atoi(result[i].substr(8).c_str());
			std::cout << "Repeat is: " << status.repeat << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="random: "){
			status.random=atoi(result[i].substr(8).c_str());
			std::cout << "Random is: " << status.random << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="single: "){
			status.single=atoi(result[i].substr(8).c_str());
			std::cout << "Single is: " << status.single << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,9)=="consume: "){
			status.consume=atoi(result[i].substr(9).c_str());
			std::cout << "Consume is: " << status.consume << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,10)=="playlist: "){
			status.playlist_revision=atoi(result[i].substr(10).c_str());
			std::cout << "Playlist Revision is: " << status.playlist_revision << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,16)=="playlistlength: "){
			status.playlist_length=atoi(result[i].substr(16).c_str());
			std::cout << "Playlist Length is: " << status.playlist_length << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,7)=="xfade: "){
			status.crossfade=atoi(result[i].substr(7).c_str());
			std::cout << "Crossfade is: " << status.crossfade << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,11)=="mixrampdb: "){ // This may get name changed 
			status.mix_ramp_on = true; // Assume it's on, disable if either of the below do so
			tmp = result[i].substr(11);
			if(tmp=="nan"){
				status.mix_ramp_on = false;
				status.mix_ramp_db = 0;
			}
			else{
				status.mix_ramp_on = true;
				status.mix_ramp_db=atoi(tmp.c_str());
			}
			std::cout << "Mix Ramp dB is: " << status.mix_ramp_db << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,14)=="mixrampdelay: "){ // This may get name changed
			tmp = result[i].substr(14);
			if(tmp=="nan"){
				status.mix_ramp_on = false;
				status.mix_ramp_delay = 0;
			}
			else{
				status.mix_ramp_on = true;
				status.mix_ramp_delay=atoi(tmp.c_str());
			}
			std::cout << "Mix Ramp On is: " << status.mix_ramp_on << std::endl;
			std::cout << "Mix Ramp Delay is: " << status.mix_ramp_delay << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,7)=="state: "){
			status.state=result[i].substr(7);
			std::cout << "State is: " << status.state << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,6)=="song: "){
			status.song_pos=atoi(result[i].substr(6).c_str());
			std::cout << "song is: " << status.song_pos << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="songid: "){
			status.song_id=atoi(result[i].substr(8).c_str());
			std::cout << "Song ID is: " << status.song_id << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,6)=="time: "){
			status.song_elapsed=atoi(result[i].substr(6,result[i].find(':')-6).c_str());
			status.song_length=atoi(result[i].substr(result[i].find(':')).c_str());
			std::cout << "Song Elapsed is: " << status.song_elapsed << std::endl;
			std::cout << "Song Length is: " << status.song_length << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,9)=="elapsed: "){
			status.song_elapsed=atof(result[i].substr(9).c_str());
			std::cout << "Song Elapsed is: " << status.song_elapsed << std::endl;
			i++;
		}
		/*if(i<result.size()) if(result[i].substr(0,9)=="bitrate: "){
			status.bitrate=atoi(result[i].substr(9).c_str());
			std::cout << "Bitrate is: " << status.bitrate << std::endl;
			i++;
		}*/
		if(i<result.size()) if(result[i].substr(0,7)=="audio: "){
			status.sample_rate=atoi(result[i].substr(7,result[i].find(':',7)-7).c_str());
			status.audio_bits=atoi(result[i].substr(result[i].find(':',7)+1, result[i].find_last_of(':')-result[i].find(':',7)).c_str());
			status.channels=atoi(result[i].substr(result[i].find_last_of(':')+1).c_str());
			std::cout << "Sample Rate is: " << status.sample_rate << std::endl;
			std::cout << "Audio Bits is: " << status.audio_bits << std::endl;
			std::cout << "Channels is: " << status.channels << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,10)=="nextsong: "){
			status.next_song=atoi(result[i].substr(10).c_str());
			std::cout << "Next Song is: " << status.next_song << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,12)=="nextsongid: "){
			status.next_song_id=atoi(result[i].substr(12).c_str());
			std::cout << "Next song ID is: " << status.next_song_id << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i]=="OK") i++; // Cave Johnson, we're done here.
		if(skipped_through){
			skipped_through=false;
			if(e==OK){
				e.short_msg = "Unknown status lines.";
				e.long_msg = "";
			}
			e.long_msg += result[i] + "\n";
			i++;
		}
		else skipped_through=true;
	}
	status.refresh_time = time(NULL);
	std::cout << "Refresh time is: " << status.refresh_time << std::endl;
	return e;
} // Tested

// Also do something to support a status fetching loop with all other operation being interrupt based

Error Connection::set_volume(int vol){ // 0-100
	if(vol>=0 && vol<=100){
		std::stringstream command;
		command << "setvol " << vol;
		return execute_or_error(command.str().c_str());
	}
	else return BAD_VOLUME;
} // Kinda tested

Error Connection::set_volume(double vol){ // 0-1
	if(vol>=0 && vol<=1)	return set_volume((int) (vol*100));
	else return BAD_VOLUME;
} // Kinda tested


//int Connection::get_bits(){ // per sample
	
Error Connection::set_crossfade(int seconds){
	std::stringstream command;
	command << "crossfade " << seconds;
	Error e = execute_or_error(command.str().c_str());
	return e;
} // Tested

/* // Maybe instead return the last error?
const char* Connection::get_mpd_error(){ // get mpd error message
	//
}*/

Error Connection::refresh_stats(){
	std::vector<std::string> result;
	result = execute_and_return("stats");
	int i = 0;
	bool skipped_through = false;
	Error e = OK;
	while(i<result.size()){
		if(result[i].substr(0,9)=="artists: "){
			stats.artists=atoi(result[i].substr(9).c_str());
			std::cout << "Artists is: " << stats.artists << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="albums: "){
			stats.albums=atoi(result[i].substr(8).c_str());
			std::cout << "Albums is: " << stats.albums << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,7)=="songs: "){
			stats.songs=atoi(result[i].substr(7).c_str());
			std::cout << "Songs is: " << stats.songs << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,8)=="uptime: "){
			stats.uptime=atoi(result[i].substr(8).c_str());
			std::cout << "Uptime is: " << stats.uptime << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,10)=="playtime: "){
			stats.time_playing=atoi(result[i].substr(10).c_str());
			std::cout << "Time playing is: " << stats.time_playing << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,13)=="db_playtime: "){
			stats.total_db_playtime=atoi(result[i].substr(13).c_str());
			std::cout << "Total DB Playtime is: " << stats.total_db_playtime << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i].substr(0,11)=="db_update: "){
			stats.last_db_update=atoi(result[i].substr(11).c_str());
			std::cout << "Last DB Update is: " << stats.last_db_update << std::endl;
			i++;
		}
		if(i<result.size()) if(result[i]=="OK") i++; // Cave Johnson, we're done here.
		if(skipped_through){
			skipped_through=false;
			if(e==OK){
				e.short_msg = "Unknown status lines.";
				e.long_msg = "";
			}
			e.long_msg += result[i] + "\n";
			i++;
		}
		else skipped_through=true;
	}
	stats.refresh_time = time(NULL);
	std::cout << "Refresh time is: " << stats.refresh_time << std::endl;
	return e;
} // Tested

Stats Connection::get_stats(){  // Tested
	refresh_stats();
	return stats;
} // Tested

/*std::vector<Album> Connection::get_albums(const Artist& artist){ // get all albums of artist (or if no artist, all albums)
	return get_albums(artist->get_name().c_str());
}*/


std::vector<Album> Connection::parse_albums(std::vector<std::string> ret){
	std::vector<Album> tmp_albums;
	for(int i=0; i<ret.size()-1; i++){
		std::cout << "Size of ret[" << i << "]: " << ret[i].size() << std::endl;
		std::cout << "ret[" << i << "]: " << ret[i] << std::endl;
		tmp_albums.push_back(Album(this, ret[i].substr(7).c_str()));
	}
	return tmp_albums;
} // Tested

std::vector<Album> Connection::get_albums(const char* artist){ // Not happy with this as it would cause multiple local objects representing the same db objects
	std::stringstream command;
	command << "list album \"" << artist << "\"";
	return parse_albums(execute_and_return(command.str().c_str()));
} // Tested


std::vector<Album> Connection::get_albums(){ // All
	return parse_albums(execute_and_return("list album"));
} // Tested

std::vector<Artist> Connection::get_artists(){
	if(artists.empty()){
		std::vector<std::string> ret = execute_and_return("list artist");
		for(int i=0; i<ret.size()-1; i++) artists.push_back(Artist(this, ret[i].substr(8).c_str()));
	}
	return artists;
} // Tested

std::vector<Artist> Connection::get_album_artists(const char* album){
	/*std::stringstream command;
	command << "list artist " << album;
	std::vector<std::string> ret = execute_and_return(command.str().c_str());
	for(int i=0; i<ret.size(); i++) artists.push_back(Artist(this, ret[i].substr(8).c_str())); */ // Needs major overhaul or abandoning
	return artists;
}

std::vector<Song> Connection::parse_songs(std::vector<std::string> ret){
	std::vector<Song> songs;
	std::string file, last_modified, time, artist, title, album, genre; 
	for(int i=0;i<ret.size();i++){
		if(ret[i].substr(0,6) == "file: "){
			
			i++;
		}
		if(ret[i].substr(0,15) == "Last-Modified: "){
			
			i++;
		}
		if(ret[i].substr(0,6) == "Time: "){
			
			i++;
		}
		if(ret[i].substr(0,8) == "Artist: "){
			
			i++;
		}
		if(ret[i].substr(0,7) == "Title: "){
			
			i++;
		}
		if(ret[i].substr(0,7) == "Album: "){
			
			i++;
		}
		if(ret[i].substr(0,7) == "Genre: "){
			
			i++;
		}
		if(ret[i] == "OK") i++;
	}	
}

std::vector<Song> Connection::get_songs_with_tag(const char* type, const char* match){
	std::stringstream command;
	command << "find " << type << " " << "\"" << match << "\"";
	return parse_songs(execute_and_return(command.str().c_str()));
}

std::vector<Song> Connection::get_artist_songs(const char* artist){ // Every song by a given artist
	return get_songs_with_tag("artist", artist);
}

std::vector<Song> Connection::get_album_songs(const char* album){ // Every song on a given album
	return get_songs_with_tag("album", album);
}

std::vector<Song> Connection::get_all_songs(){ // Every song
	if(songs.empty()){
		std::vector<std::string> ret=execute_and_return("listallinfo");
		for(int i=0; i<ret.size(); i++){
			
		} // TODO Come back to this, remember to skip over directories and playlists
	}
	return songs;
}

Error Connection::update_dir(const char* path){ // "update (parts of) the database" whut?
	std::stringstream command;
	command << "update \"" << path << "\"";
	return execute_or_error(command.str().c_str());
}

//find(const char* type, const char* needle, bool exact); // depreciated, may or may not bring back 

std::vector<FileSystemEntry> Connection::get_directory(const char* directory_path){ //returns songs, directories and playlists (I think all of those are files)
	std::stringstream command;
	command << "lsinfo \"" << directory_path << "\"";
	std::vector<std::string> ret=execute_and_return(command.str().c_str());
	std::vector<FileSystemEntry> files;
	// TODO
	return files;
}

std::vector<FileSystemEntry> Connection::get_directory_recursive(const char* directory_path){ // like the above
	// TODO similar to get_all_songs()
	std::vector<FileSystemEntry> files;
	// TODO
	return files;
}

// The functionality of this goes into the Song class 
// Hmm maybe not exactly, I don't know how the API user would get a file path but not the Song object, but it could happen
// The real question is, do I care enough to code this?
/*Song get_fileinfo(const char* file_path){
	//
}*/

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


/*Error Connection::queue_add(Song s){ // add to current queue
	
}
Error Connection::queue_remove(Song s){ // remove from current queue
	
}*/
//libmpd


Connection::Connection(const char* hn, int pt, const char* pw, float to){
	hostname=hn;
	port=pt;
	password=pw;
	timeout=to;
	
	//currentSong=EMPTY_SONG; // Or something
	elapsedSong=0;
		
	status=Status();
	
	stats=Stats();
	lock_flag=false;
	// Perhaps zero out some other variables
} // Tested

void Connection::set_hostname(const char* hn){
	hostname = hn;
}

const char* Connection::get_hostname(){
	return hostname.c_str();
}

void Connection::set_password(const char* pw){
	password=pw;
}

// get_password() Hmmm, hello security issue

void Connection::set_connection_timeout(float to){
	timeout=to;
}

int Connection::get_connection_timeout(){
	return timeout;
}

Error Connection::connect(){
	int retv; // What was I thinking with this?
 
	// Clear error

	if(!connected) disconnect();
	
	if(!lock()) return LOCK_FAILURE;
	
	std::string welcome_msg;
	
	try{
		socket.connect(hostname, port);
   	socket.add_delim("\n");
   	socket >> welcome_msg;
	}
	catch(Network::Exception e){
		std::cout << "Got a connection error of: " << e.get_error() << std::endl;
		// Return an MPD::Exception 
	}
	 
	// Parse the welcome message to make sure this is MPD and what version it is
	// Should be of the form "OK MPD %i.%i.%i" (major, minor, micro) version
	std::cout << welcome_msg << std::endl;
	if(welcome_msg.substr(0,7)!="OK MPD ") return NOT_MPD_CONNECTION;
	std::string::size_type first_dot = welcome_msg.find(".", 7);
	std::string::size_type second_dot = welcome_msg.find(".", first_dot);
	if(first_dot==std::string::npos || second_dot==std::string::npos) return BAD_MPD_VERSION;
	version.major=atoi(welcome_msg.substr(7,first_dot-7).c_str());
	version.minor=atoi(welcome_msg.substr(first_dot, second_dot-first_dot).c_str());
	version.micro=atoi(welcome_msg.substr(second_dot).c_str());
	
	// Refresh the status
	refresh_status();
	
	connected = true;
	unlock();

	// refresh the list of supported commands
	//refresh_allowed_commands();
   
	// refresh the list of outputs
   //refresh_outputs();
   
   // refresh the tag types
   //refresh_tag_types();
  
   // emit the necessary signals
   
    return OK;
} // Tested

Error Connection::disconnect(){
	lock();
	
	// Close the socket
	try{
		socket.close();
	}
	catch(Network::Exception e){
		// convert to MPD error
	}

	// Empty status

	// Empty stats

	// Empty current song

	// Empty state

	// Reset search
	
	// Empty output devices

   // Empty supported tags

	// Reset has_idle

	// clear_queue();
	
	// clear_command_list();
		
	// Leave error alone so the cause of disconnecting can be investigated if needed
	
	connected = false;

	// Emit signal
	
	unlock();
	 
	return OK;

}

bool Connection::check_connected(){
	return connected;
}

Error Connection::check_error(){
	// if there is an error, return it
	// Hmm, do I want/need this?
}

Connection::~Connection(){
	disconnect();
}
	
Error Connection::send_password(){ // re-auth
	if(password!="" && connected){
		std::stringstream command;
		command << "password \"" << password << "\"";
		Error e = execute_or_error(command.str().c_str());
		if(e){
			refresh_allowed_commands();
			// Emit signals
		}
		else return e;
	}
	return OK;
}

std::vector<OutputDevice> Connection::get_output_devices(){
	if(output_devices.empty()){
		std::vector<std::string> ret = execute_and_return("outputs");
		int output_id;
		std::string output_name;
		bool output_enabled; 
		for(int i=0; i<ret.size(); i++){
			output_id=atoi(ret[i].substr(10).c_str());
			i++; // Skip to the next line
			output_name=ret[i].substr(12);
			i++; // Skip to the next line
			output_enabled=atoi(ret[i].substr(15).c_str());
			output_devices.push_back(OutputDevice(this, output_id, output_name.c_str(), output_enabled));
		}
	}
	return output_devices;		
}

Error Connection::set_output_device(OutputDevice od, bool e){
	return set_output_device(od.get_id(),e);
}

Error Connection::enable_output_device(OutputDevice od){
	enable_output_device(od.get_id());
}

Error Connection::disable_output_device(OutputDevice od){
	disable_output_device(od.get_id());
}

Error Connection::flip_output_device(OutputDevice od){
	if(od.get_enabled()) return disable_output_device(od.get_id());
	else return enable_output_device(od.get_id());
}

Error Connection::set_output_device(int od_id, bool e){
	if(e) return enable_output_device(od_id);
	else return disable_output_device(od_id);
}

Error Connection::enable_output_device(int od_id){
	std::stringstream command;
	command << "enableoutput" << od_id << "\""; 
	return execute_or_error(command.str().c_str());
}

Error Connection::disable_output_device(int od_id){
	std::stringstream command;
	command << "disableoutput" << od_id << "\""; 
	return execute_or_error(command.str().c_str());
}

Error Connection::flip_output_device(int od_id){
	// Might not support this because it probably requires an extra server hit
}

bool Connection::check_version(int major, int minor, int micro){
	if(version.major>major) return true;
	if(version.major<major) return false;
	if(version.minor>minor) return true;
	if(version.minor<minor) return false;
	if(version.micro>micro) return true;
	if(version.micro<micro) return false;
}

const char* Connection::get_version(){
	std::stringstream ss;
	ss << version.major << "." << version.minor << "." << version.micro;
	return ss.str().c_str(); 
}

//check_command_allowed()

std::vector<std::string> Connection::get_url_handlers(){ // List of url prefixes that the server understands (http:// ftp:// etc.)
	if(url_handlers.empty()){
		std::vector<std::string> ret=execute_and_return("urlhandlers");
		for(int i=0; i<ret.size(); i++) url_handlers.push_back(ret[i].substr(9));
	}
	return url_handlers;
}

std::vector<std::string> Connection::get_tag_types(){
	// TODO
}

//get_tag_by_name() // probably don't need this

bool Connection::server_has_idle(){
	return has_idle;
}

bool Connection::is_tag_supported(const char* t){ // TagType must be able to convert to const char*
	// idk
}

std::vector<std::string> Connection::execute_and_return(const char* command){
	std::vector<std::string> ret;
	try{
		start_execute(command);
		// Get the return messages
		std::string tmp="";
		while(tmp!="OK" && tmp.substr(0,3)!="ACK"){
			socket >> tmp;
			ret.push_back(tmp);
		}
	}
	catch(Network::Exception e){
		// Convert to an MPD Error
	}
	finish_execute();
	return ret;
}


void Connection::start_execute(const char* command){
	//std::cout << "In start_execute" << std::endl;
	if(!connected) {
		//debug_printf(DEBUG_WARNING, "not connected\n");
		//throw MPD_NOT_CONNECTED;
	}
	if(!lock()){
		//debug_printf(DEBUG_WARNING, "lock failed\n");
		//throw MPD_LOCK_FAILED;
	}
	
	// Make sure there aren't any other commands still being processed
	// Wait I think that's taken care of with the lock...
	
	// Clear error (maybe it should be an error queue?)
	
	// Send the command
	std::cout << "About to try socket << " << command << std::endl;
	socket << command << "\n";
	std::cout << "Finished socket << command" << std::endl;
}

void Connection::finish_execute(){
	//std::cout << "In finish_execute" << std::endl;
	unlock();
	/*if(!status_update()) { // This might get incorporated if the above is rewritten
		//throw MPD_STATUS_FAILED;
	}*/
}

Error Connection::execute_or_error(const char* command){
	try{
		start_execute(command);
		std::string tmp;
		while(tmp!="OK" && tmp.substr(0,3)!="ACK"){
			std::cout << "Next line is:" << std::endl;
			socket >> tmp; // Skip through the return messages
			std::cout << tmp << std::endl;
		}
		finish_execute();
		refresh_status();
	}
	catch(Network::Exception e){
		std::cout << "Got a network exception error of" << e.get_error() << std::endl;
		// convert to an MPD error and return it
		return OK;
	}
	catch(Error e){
		return e;
	} 
	return OK;
}


Error Connection::refresh_allowed_commands(){
	// TODO
}

Error Connection::refresh_current_stats(){
	
}

Error Connection::refresh_current_song(){
	
}

Error Connection::refresh_playlist_info(){  // Differnce?

}

Error Connection::refresh_playlist_id(){ // ^

}

}
