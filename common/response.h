#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

namespace jerrymusic {

using json = nlohmann::json;

// 统一返回体：{ code, message, data }
inline std::string makeResponse(int code, const std::string& message, const json& data = json::object()) {
    json resp;
    resp["code"] = code;
    resp["message"] = message;
    resp["data"] = data;
    std::cout << "rep = " << resp.dump() << std::endl;
    return resp.dump();
}

inline std::string ok(const json& data = json::object()) {
    return makeResponse(0, "ok", data);
}

inline std::string error(int code, const std::string& message) {
    return makeResponse(code, message);
}

} // namespace jerrymusic
