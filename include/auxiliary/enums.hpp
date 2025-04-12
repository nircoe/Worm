#pragma once

namespace Enums
{
    enum class Difficulty 
    {
        Easy = 10,
        Medium = 20,
        Hard = 30,
        Impossible = 60
    };

    enum class SceneName
    {
        New_Game_Scene = 0,
        Home_Scene = 1,
        Game_Scene = 2
    };

    enum class HomeButton
    {
        None = -1,
        Play = 0,
        Exit = 1,
        Easy = 2,
        Medium = 3,
        Hard = 4,
        Impossible = 5
    };

    enum class GameButton
    {
        None = -1,
        Home_Screen = 0,
        Play_Again = 1,
        Exit = 2
    };

    enum class NewGameButton
    {
        None = -1,
        Continue = 0,
        Guest = 1
    };
}