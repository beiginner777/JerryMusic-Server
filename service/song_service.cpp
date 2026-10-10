#include "song_service.h"
#include "../dao/song_dao.h"
#include "../common/response.h"

namespace jerrymusic {

std::string SongService::listSongs() {
    SongDao dao;
    return ok({{"songs", dao.listSongs()}});
}

std::string SongService::searchSongs(const std::string& keyword) {
    if (keyword.empty()) {
        return error(1003, "keyword is required");
    }
    SongDao dao;
    return ok({{"songs", dao.searchSongs(keyword)}});
}

} // namespace jerrymusic
