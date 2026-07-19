cmake_minimum_required(VERSION 3.16)

project(com LANGUAGES C)

# Додаємо шлях до бібліотеки MAVLink
include_directories(${CMAKE_SOURCE_DIR}/mavlink/c_library_v2)

add_executable(com main.c
    serial.h
    serial.c
    serial_thread.h
    serial_thread.c
    mavlink_handler.h
    mavlink_handler.c
)

include(GNUInstallDirs)
install(TARGETS com
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
