set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ultralight_tilde) # output bundle: airfx.ultralight~.mxo (_tilde->~)

target_sources(airfx.ultralight_tilde
    PRIVATE
        airfx.ultralight_tilde.cpp)

target_include_directories(airfx.ultralight_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ultralight_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
