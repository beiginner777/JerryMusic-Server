#include "song_handler.h"

namespace jerrymusic {

std::string SongHandler::handleList() {
    return service_.listSongs();
}

std::string SongHandler::handleSearch(const std::string& query) {
    return service_.searchSongs(query);
}

} // namespace jerrymusic
