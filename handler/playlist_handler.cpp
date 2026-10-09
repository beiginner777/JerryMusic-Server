#include "playlist_handler.h"

namespace jerrymusic {

std::string PlaylistHandler::handleList() {
    return service_.listPlaylists();
}

} // namespace jerrymusic
