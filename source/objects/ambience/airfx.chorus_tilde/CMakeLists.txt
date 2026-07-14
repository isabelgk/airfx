set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chorus_tilde) # output bundle: airfx.chorus~.mxo (_tilde->~)

target_sources(airfx.chorus_tilde
    PRIVATE
        airfx.chorus_tilde.cpp)

target_include_directories(airfx.chorus_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chorus_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
