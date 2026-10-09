#include "song_handler.h"

namespace jerrymusic {

std::string SongHandler::handleList() {
    return service_.listSongs();
}

} // namespace jerrymusic
