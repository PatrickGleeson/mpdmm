// Common header file that includes all other necessary headers in the correct order


#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <socket/tcpsocket.hh>

namespace Mpd{

class Error;
class FileSystemEntry;
class Song;
class Album;
class Artist;
class Directory;
class Playlist;
class OutputDevice;
class Status;
class Stats;
class Connection;

#include "Error.h"
#include "FileSystemEntry.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"
// #include "Directory.h"
// #include "Playlist.h"
#include "OutputDevice.h"
#include "Status.h"
#include "Stats.h"
#include "Connection.h"

}