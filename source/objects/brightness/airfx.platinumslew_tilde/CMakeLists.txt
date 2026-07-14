set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.platinumslew_tilde) # output bundle: airfx.platinumslew~.mxo (_tilde->~)

target_sources(airfx.platinumslew_tilde
    PRIVATE
        airfx.platinumslew_tilde.cpp)

target_include_directories(airfx.platinumslew_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.platinumslew_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
