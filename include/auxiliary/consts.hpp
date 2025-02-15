#pragma once

#include "raylib-cpp.hpp"
#include "enums.hpp"
#include "colors.hpp"
#include <string>
#include <array>
#include <deque>

namespace Consts
{
    const std::string GAME_NAME = "Worm";
    const std::string GAME_OVER_TEXT = "Game Over!";
    const std::string FONT_PATH = "C:/Projects/Worm/assets/fonts/joystix_monospace.otf";
    const std::string ICON_IMAGE_PATH = "C:/Projects/Worm/assets/images/icon.png";

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const int GAME_OVER_FONT_SIZE = 40;
    const int TITLE_FONT_SIZE = 80;
    const int START_GAME_FONT_SIZE = 24;
    const int BUTTONS_FONT_SIZE = 20;
    const int NUM_OF_SCENES = 2;

    const float PLAYER_SPEED = 23.0f;
    const float DIAGONAL_MULTIPLY = 1.352f;
    const float FOOD_SIZE = 15.0f;
    const float PLAYER_HEAD_RADIUS = 12.0f;
    const float PLAYER_BODY_RADIUS = 10.0f;
    const float FOOD_SPAWN_MARGIN = 50.0f;
    const float GAME_OVER_TO_SCORE_GAP = 30.0f;

    const raylib::Vector2 HALF_SCREEN(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    const raylib::Vector2 SCREEN_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);
    const std::deque<raylib::Vector2> INITIAL_PLAYER_BODY = { HALF_SCREEN, HALF_SCREEN, HALF_SCREEN };
    const std::vector<raylib::Rectangle> BORDERS = {
        { -1.0f, -1.0f, 10.0f, SCREEN_HEIGHT + 1.0f },
        { -1.0f, -1.0f, SCREEN_WIDTH + 1.0f, 10.0f },
        { -1.0f, SCREEN_HEIGHT - 10.0f, SCREEN_WIDTH + 1.0f, 10.0f },
        { SCREEN_WIDTH - 10.0f, -1.0f, 10.0f, SCREEN_HEIGHT + 1.0f }
    };

    const std::vector<raylib::Rectangle> IMPOSSIBLE_BORDERS = {
        { -1.0f, -1.0f, 30.0f, SCREEN_HEIGHT + 1.0f },
        { -1.0f, -1.0f, SCREEN_WIDTH + 1.0f, 30.0f },
        { -1.0f, SCREEN_HEIGHT - 30.0f, SCREEN_WIDTH + 1.0f, 30.0f },
        { SCREEN_WIDTH - 30.0f, -1.0f, 30.0f, SCREEN_HEIGHT + 1.0f }
    };

    const raylib::Rectangle PLAY_BUTTON_RECT(300, 450, 200, 60);
    const raylib::Rectangle EXIT_BUTTON_RECT(300, 520, 200, 60);
    const raylib::Rectangle EASY_BUTTON_RECT(60, 250, 150, 70);
    const raylib::Rectangle MEDIUM_BUTTON_RECT(230, 250, 150, 70);
    const raylib::Rectangle HARD_BUTTON_RECT(395, 250, 150, 70);
    const raylib::Rectangle IMPOSSIBLE_BUTTON_RECT(565, 250, 150, 70);

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    const std::array<const std::string, 6> HOME_BUTTONS_TEXTS = {  
        "Play",
        "Exit",
        "Easy",
        "Medium",
        "Hard",
        "Impossible" };

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    const std::array<const raylib::Rectangle, 6> HOME_BUTTONS_RECTS = {
        Consts::PLAY_BUTTON_RECT,
        Consts::EXIT_BUTTON_RECT,
        Consts::EASY_BUTTON_RECT,
        Consts::MEDIUM_BUTTON_RECT,
        Consts::HARD_BUTTON_RECT,
        Consts::IMPOSSIBLE_BUTTON_RECT };

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible   
    const std::array<Enums::HomeButton, 6> HOME_BUTTONS_IDS = {
        Enums::HomeButton::Play,
        Enums::HomeButton::Exit,
        Enums::HomeButton::Easy,
        Enums::HomeButton::Medium,
        Enums::HomeButton::Hard,
        Enums::HomeButton::Impossible };

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    const std::array<raylib::Color, 6> HOME_BUTTONS_HOVER_COLORS = {
        Colors::BUTTON_HOVER_COLOR,
        Colors::BUTTON_HOVER_COLOR,
        Colors::EASY_HOVER_COLOR,
        Colors::MEDIUM_HOVER_COLOR,
        Colors::HARD_HOVER_COLOR,
        Colors::IMPOSSIBLE_HOVER_COLOR };

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    const std::array<raylib::Color, 6> HOME_BUTTONS_CLICKED_COLORS = {
        Colors::BUTTON_CLICKED_COLOR,
        Colors::BUTTON_CLICKED_COLOR,
        Colors::EASY_CLICKED_COLOR,
        Colors::MEDIUM_CLICKED_COLOR,
        Colors::HARD_CLICKED_COLOR,
        Colors::IMPOSSIBLE_CLICKED_COLOR };

    //  0  ,   1   ,  2  ,     3
    // Easy, Medium, Hard, Impossible
    const std::array<Enums::Difficulty, 4> DIFFICULTIES_ARRAY = {
        Enums::Difficulty::Easy,
        Enums::Difficulty::Medium,
        Enums::Difficulty::Hard,
        Enums::Difficulty::Impossible
    };

    const Enums::Difficulty STARTING_DIFFICULTY = Enums::Difficulty::Easy;

    // GAME OVER UI

    const raylib::Rectangle GAME_OVER_MAIN_MENU_BUTTON_RECT(80, 480, 200, 60);
    const raylib::Rectangle GAME_OVER_PLAY_AGAIN_BUTTON_RECT(300, 480, 200, 60);
    const raylib::Rectangle GAME_OVER_EXIT_BUTTON_RECT(520, 480, 200, 60);

    //     0          1        2
    // Main Menu, Play Again, Exit
    const std::array<const raylib::Rectangle, 3> GAME_OVER_RECTS = {
        Consts::GAME_OVER_MAIN_MENU_BUTTON_RECT,
        Consts::GAME_OVER_PLAY_AGAIN_BUTTON_RECT,
        Consts::GAME_OVER_EXIT_BUTTON_RECT };

    //     0          1        2
    // Main Menu, Play Again, Exit
    const std::array<const std::string, 3> GAME_OVER_BUTTONS_TEXT = {
        "Main Menu",
        "Play Again",
        "Exit" };

    const std::array<Enums::GameButton, 3> GAME_OVER_BUTTONS_ID = {
        Enums::GameButton::Home_Screen,
        Enums::GameButton::Play_Again,
        Enums::GameButton::Exit };

} // namespace Consts
