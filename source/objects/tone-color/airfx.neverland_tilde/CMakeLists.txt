set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.neverland_tilde) # output bundle: airfx.neverland~.mxo (_tilde->~)

target_sources(airfx.neverland_tilde
    PRIVATE
        airfx.neverland_tilde.cpp)

target_include_directories(airfx.neverland_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.neverland_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
