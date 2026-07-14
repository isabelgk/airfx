set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.multibanddistortion_tilde) # output bundle: airfx.multibanddistortion~.mxo (_tilde->~)

target_sources(airfx.multibanddistortion_tilde
    PRIVATE
        airfx.multibanddistortion_tilde.cpp)

target_include_directories(airfx.multibanddistortion_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.multibanddistortion_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
