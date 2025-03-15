#include "data_management/game_data.hpp"
#include <iostream>
#include <stdexcept>

GameData::GameData(const std::string &nickname) : m_nickname(nickname), m_highScores({0}) { }

void GameData::setNickName(const std::string &nickname) 
{
    m_nickname = nickname;
}

void GameData::setHighScore(int difficulty, int highscore)
{
    if(m_highScores[difficulty] < highscore)
        m_highScores[difficulty] = highscore;
}

const std::string &GameData::getNickName() const
{
    return m_nickname;
}

json GameData::toJson() const
{
    json j;
    j["nickname"] = m_nickname;
    j["highScores"] = m_highScores;
    return j;
}

GameData GameData::fromJson(const json &j)
{
    GameData gameData;
    if(j.contains("nickname") && j["nickname"].is_string())
        gameData.m_nickname = j["nickname"].get<std::string>();
    else
        throw std::runtime_error("'nickname' key is missing or invalid in the JSON object we are trying to load.");

    if(j.contains("highScores") && j["highScores"].is_array() && j["highScores"].size() == 4)
    {
        try { gameData.m_highScores = j["highScores"].get<std::array<int, 4>>(); }
        catch(const json::exception& e) { throw; }
    }
    else
        throw std::runtime_error("'highScores' key is missing or invalid in the JSON object we are trying to load.");

    return std::move(gameData);
}
