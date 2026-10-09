#include "song_service.h"
#include "../dao/song_dao.h"
#include "../common/response.h"

namespace jerrymusic {

std::string SongService::listSongs() {
    SongDao dao;
    return ok({{"songs", dao.listSongs()}});
}

} // namespace jerrymusic
