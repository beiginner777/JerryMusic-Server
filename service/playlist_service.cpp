#include "playlist_service.h"
#include "../dao/playlist_dao.h"
#include "../common/response.h"

namespace jerrymusic {

std::string PlaylistService::listPlaylists() {
    PlaylistDao dao;
    return ok({{"playlists", dao.listPlaylists()}});
}

} // namespace jerrymusic
