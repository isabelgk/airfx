set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.autopan_tilde) # output bundle: airfx.autopan~.mxo (_tilde->~)

target_sources(airfx.autopan_tilde
    PRIVATE
        airfx.autopan_tilde.cpp)

target_include_directories(airfx.autopan_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.autopan_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
