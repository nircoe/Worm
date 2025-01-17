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
        None,
        Play,
        Exit,
        Easy,
        Medium,
        Hard,
        Impossible
    };

    enum class GameButton
    {
        None,
        Home_Screen,
        Play_Again,
        Exit
    };
}