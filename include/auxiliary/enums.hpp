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
        Home_Scene = 0,
        Game_Scene = 1
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
}