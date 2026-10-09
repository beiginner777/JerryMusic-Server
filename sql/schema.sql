-- JerryMusic 后端数据库 Schema（阶段 2）

-- 用户表
CREATE TABLE IF NOT EXISTS users (
    id            BIGSERIAL PRIMARY KEY,
    username      VARCHAR(64) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,   -- 存哈希，不存明文
    created_at    TIMESTAMPTZ DEFAULT NOW()
);

-- 歌曲表（字段对齐客户端 core:model.Song 和接口协议）
CREATE TABLE IF NOT EXISTS songs (
    id          BIGSERIAL PRIMARY KEY,
    title       VARCHAR(255) NOT NULL,
    artist      VARCHAR(255) NOT NULL,
    uri         TEXT NOT NULL,             -- 音频播放地址
    cover_url   TEXT DEFAULT '',
    duration_ms BIGINT DEFAULT 0
);

-- 歌单表（阶段 2 只存元信息；user_id 阶段 6 再加）
CREATE TABLE IF NOT EXISTS playlists (
    id         BIGSERIAL PRIMARY KEY,
    name       VARCHAR(255) NOT NULL,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

-- 种子数据（测试用）
INSERT INTO songs (title, artist, uri, duration_ms) VALUES
    ('Song 1', 'SoundHelix', 'https://www.soundhelix.com/examples/mp3/SoundHelix-Song-1.mp3', 300000),
    ('Song 2', 'SoundHelix', 'https://www.soundhelix.com/examples/mp3/SoundHelix-Song-2.mp3', 300000),
    ('Song 3', 'SoundHelix', 'https://www.soundhelix.com/examples/mp3/SoundHelix-Song-3.mp3', 300000)
ON CONFLICT DO NOTHING;

INSERT INTO playlists (name) VALUES ('推荐歌单')
ON CONFLICT DO NOTHING;
