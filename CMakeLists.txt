cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FLTK_ROOT "C:/Program Files (x86)/FLTK/bin")
find_package(FLTK REQUIRED)

project(ToDoList)

set(TARGET "ToDoList")

add_executable(
        ${TARGET}
        src/MainWindowPart/main.cpp
        src/Graph_lib/Graph.cpp
        src/Graph_lib/GUI.cpp
        src/Graph_lib/Window.cpp
        src/Graph_lib/Window.cpp
        src/DayWork/DayDraw.cpp
        src/DayWork/MyButton.cpp
        src/DayWork/ChangeTaskInfo.cpp
        src/DayWork/ChangeTaskInfo.h
        src/DayWork/MyButton.h
        src/DayWork/TaskWindow.cpp
        src/DayWork/TaskWindow.h
        src/DayWork/PARAMETERS.h
        src/MainWindowPart/MainWindow.cpp
        src/MainWindowPart/MainWindow.h
        src/MainWindowPart/year.h
        src/MainWindowPart/year.cpp
        src/MainWindowPart/month.cpp
        src/MainWindowPart/month.h
        src/toDoListFileWork/to_do_list/task_manager2.cpp
        src/toDoListFileWork/to_do_list/chrono.cpp
        src/toDoListFileWork/to_do_list/chrono.h
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