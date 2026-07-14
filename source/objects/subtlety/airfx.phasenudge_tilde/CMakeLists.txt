set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.phasenudge_tilde) # output bundle: airfx.phasenudge~.mxo (_tilde->~)

target_sources(airfx.phasenudge_tilde
    PRIVATE
        airfx.phasenudge_tilde.cpp)

target_include_directories(airfx.phasenudge_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.phasenudge_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
