cmake_minimum_required(VERSION 3.0.2)
project(provagui)
find_package(Qt4 4.4.3 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})



set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

set(provaGui_SRCS test.cpp scene.cpp provapopup.cpp provaGui.cpp main.cpp prova_widget.cpp provariquadro.cpp handleitem.cpp provaporte.cpp arrow.cpp portselect.cpp)

#qt4_automoc(${provaGui_SRCS})

add_executable(provagui ${provaGui_SRCS})
target_link_libraries(provagui ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS provagui RUNTIME DESTINATION bin)
