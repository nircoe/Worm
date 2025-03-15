#pragma once

#include <string>
#include <array>
#include "json.hpp"

using json = nlohmann::json;

class GameData 
{
    std::string m_nickname;
    std::array<int, 4> m_highScores;

public:
    GameData(const std::string& nickname = "");

    void setNickName(const std::string& nickname);
    void setHighScore(int difficulty, int highscore);

    const std::string& getNickName() const;

    json toJson() const;

    static GameData fromJson(const json& j);    
};