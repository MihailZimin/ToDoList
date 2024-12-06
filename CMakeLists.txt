cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FLTK_ROOT "C:/Program Files (x86)/FLTK/bin")
find_package(FLTK REQUIRED)

project(LogicElements)

set(TARGET "Day")

add_executable(
        ${TARGET}
        MainWindowPart/main.cpp
        src/Graph_lib/Graph.cpp
        src/Graph_lib/GUI.cpp
        src/Graph_lib/Window.cpp
        src/DayLogic.cpp
        src/DayDraw.cpp
        src/MyButton.cpp
        src/ChangeTaskInfo.cpp
        src/ChangeTaskInfo.h
        src/MyButton.h
        src/TaskWindow.cpp
        src/TaskWindow.h
        src/PARAMETERS.h
        MainWindowPart/day.cpp
        MainWindowPart/day.h
        MainWindowPart/MainWindow.cpp
        MainWindowPart/MainWindow.h
)

target_include_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${FLTK_INCLUDE_DIR}
)

target_link_directories(${TARGET} PRIVATE
        ${FLTK_INCLUDE_DIR}/../lib
)

target_link_libraries(${TARGET} PRIVATE
        ${FLTK_LIBRARIES}
        fltk_jpeg
        fltk_png
        fltk_z
)

add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
        COMMENT "Copying resources into runtime output directory"
)

add_dependencies(${TARGET} CopyResources)