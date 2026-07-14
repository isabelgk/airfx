set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.vibrato_tilde) # output bundle: airfx.vibrato~.mxo (_tilde->~)

target_sources(airfx.vibrato_tilde
    PRIVATE
        airfx.vibrato_tilde.cpp)

target_include_directories(airfx.vibrato_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.vibrato_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
