#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <utility>

namespace jerrymusic {

/**
 * 歌单表数据访问（PostgreSQL / libpq）。
 */
class PlaylistDao {
public:
    // 查询所有歌单，返回 JSON 数组
    nlohmann::json listPlaylists();

    // 按 id 查歌单，返回 (id, name)；不存在返回 nullopt
    std::optional<std::pair<long, std::string>> getPlaylistById(long playlistId);

    // 查歌单里的所有歌曲
    nlohmann::json getPlaylistSongs(long playlistId);

    // 把歌加进歌单（重复则忽略），成功返回 true
    bool addSongToPlaylist(long playlistId, long songId);
};

} // namespace jerrymusic
