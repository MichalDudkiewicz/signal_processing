cmake_minimum_required(VERSION 3.17)
project(program)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/local/pkg/qt/qt-5.6.3/5.6.3/gcc_64/lib/cmake/Qt5Quick")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/main_window.cpp
        include/main_window.hpp
        src/signal_display_widget.cpp
        include/signal_display_widget.hpp
        src/result_signal_dialog.cpp
        include/result_signal_dialog.hpp
        )

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

target_include_directories(program PRIVATE include)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} Charts REQUIRED)
target_link_libraries(${PROJECT_NAME} library ${REQUIRED_LIBS_QUALIFIED} Qt5Charts)
