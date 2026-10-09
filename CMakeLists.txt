cmake_minimum_required(VERSION 3.20)
project(JerryMusic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg 安装根目录（x64-mingw-dynamic triplet）
set(VCPKG_ROOT "E:/File/vcpkg/vcpkg/installed/x64-mingw-dynamic")

# ===== 主服务端 =====
add_executable(JerryMusic
    main.cpp
    handler/auth_handler.cpp
    handler/song_handler.cpp
    handler/playlist_handler.cpp
    service/auth_service.cpp
    service/song_service.cpp
    service/playlist_service.cpp
    dao/user_dao.cpp
    dao/song_dao.cpp
    dao/playlist_dao.cpp
)

target_include_directories(JerryMusic PRIVATE
    "D:/Program Files/boost"                      # boost (beast / asio)
    "${VCPKG_ROOT}/include"                       # jwt-cpp / nlohmann-json / openssl
    "D:/Program Files/PostgreSQL/17/include"      # libpq-fe.h
)

target_link_libraries(JerryMusic PRIVATE
    "D:/Program Files/PostgreSQL/17/lib/libpq.lib"  # libpq（PostgreSQL 自带）
    "${VCPKG_ROOT}/lib/libssl.dll.a"                # openssl libssl（jwt-cpp + sha256）
    "${VCPKG_ROOT}/lib/libcrypto.dll.a"             # openssl libcrypto
    ws2_32                                          # winsock（asio）
    mswsock                                         # AcceptEx / GetAcceptExSockaddrs
)

# ===== PostgreSQL 连接测试（libpq）=====
add_executable(pg_test test/pg_test.cpp)
target_include_directories(pg_test PRIVATE "D:/Program Files/PostgreSQL/17/include")
target_link_libraries(pg_test PRIVATE "D:/Program Files/PostgreSQL/17/lib/libpq.lib")
