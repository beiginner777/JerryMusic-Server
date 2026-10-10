#pragma once
#include <string>

namespace jerrymusic {

/**
 * 歌单业务逻辑。
 */
class PlaylistService {
public:
    std::string listPlaylists();

    std::string getPlaylistDetail(long playlistId);

    std::string addSongToPlaylist(long playlistId, long songId);
};

} // namespace jerrymusic
