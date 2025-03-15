#pragma once

#include <string>
#include <optional>
#include "game_data.hpp"
#include "data_reader_writer.hpp"
#include "../auxiliary/enums.hpp"
#include "../game_manager.hpp"

class DataManager
{
    std::string m_filename;
    GameData m_gamedata;

    bool load();

public:
    DataManager() = default;

    void init(GameManager& gameManager, const std::string filename);

    void newGame(std::string nickname);

    bool save();

    void setNickName(std::string nickname);
    void setHighScore(Enums::Difficulty difficulty, int highscore);

    GameData getGameData() const;
};