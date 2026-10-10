#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace jerrymusic {

/**
 * 歌曲表数据访问（PostgreSQL / libpq）。
 */
class SongDao {
public:
    // 查询所有歌曲，返回 JSON 数组
    nlohmann::json listSongs();

    // 按关键词模糊搜索歌曲（title / artist）
    nlohmann::json searchSongs(const std::string& keyword);
};

} // namespace jerrymusic
