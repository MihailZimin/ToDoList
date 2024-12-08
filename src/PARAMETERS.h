//
// Created by Misha on 26.11.2024.
//

#ifndef PARAMETERS_H
#define PARAMETERS_H

constexpr int BUTTON_WIDTH = 80;
constexpr int BUTTON_HEIGHT = 50;
constexpr int MARGIN = 20;
constexpr int START_BUTTONS_POSITION_X = 40;
constexpr int START_BUTTONS_POSITION_Y = 40;
constexpr Graph_lib::Point START_TEXT_POSITION{20, 90};
constexpr Graph_lib::Point START_TEXT_TIME_POSITION{20, 70};
constexpr Graph_lib::Point START_INBOX_POSITION{170, 10};
constexpr int BASIC_WINDOW_WIDTH = 600;
constexpr int BASIC_WINDOW_HEIGHT = 400;
constexpr  Graph_lib::Point BASIC_WINDOW_POSITION{100, 100};
const std::string NOTE1 = "NOTE: if you will enter wrong time (hours < 0 or > 23, minutes < 0 or > 59)";
const std::string NOTE2 = "time will be setted default: 00:00";
constexpr unsigned INVALID_TIME = 100;

#endif //PARAMETERS_H
