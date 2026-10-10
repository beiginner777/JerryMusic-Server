#include "playlist_service.h"
#include "../dao/playlist_dao.h"
#include "../common/response.h"

namespace jerrymusic {

std::string PlaylistService::listPlaylists() {
    PlaylistDao dao;
    return ok({{"playlists", dao.listPlaylists()}});
}

std::string PlaylistService::getPlaylistDetail(long playlistId) {
    PlaylistDao dao;
    auto playlist = dao.getPlaylistById(playlistId);
    if (!playlist) {
        return error(1004, "playlist not found");
    }
    auto [id, name] = *playlist;
    json p = {{"id", std::to_string(id)}, {"name", name}};
    return ok({{"playlist", p}, {"songs", dao.getPlaylistSongs(playlistId)}});
}

std::string PlaylistService::addSongToPlaylist(long playlistId, long songId) {
    PlaylistDao dao;
    if (!dao.addSongToPlaylist(playlistId, songId)) {
        return error(1005, "add song failed");
    }
    return ok();
}

} // namespace jerrymusic
