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
const std::string NOTE0_0 = "NOTE: Check NOTE in day window";
const std::string NOTE0 = "NOTE: 1) you should enter time in pattern: hours:minutes;";
const std::string NOTE1 = "2) if you will enter wrong time (hours < 0 or > 23, minutes < 0 or > 59)";
const std::string NOTE2 = "time will be setted default: start - 00:00, end - 01:01;";
const std::string NOTE3 = "3) If you will enter wrong day, year or month those parameters will be";
const std::string NOTE4 = "setted default;";
const std::string NOTE5 = "4) default parameters: start - 00:00, end - 01:01, end date: current day date";
const std::string NOTE6 = "5) your task information need to be not really long if you want to see all task info";
constexpr unsigned INVALID_TIME = 100;
constexpr int FIELDS_START_POSITION_X = 170;
constexpr int FIELDS_START_POSITION_Y = 10;
constexpr int FIELD_HEIGHT = 30;
constexpr int FIELD_WIDTH = 80;
constexpr int START_NOTES = 300;
constexpr int NOTES_SIZE = 20;

#endif //PARAMETERS_H
