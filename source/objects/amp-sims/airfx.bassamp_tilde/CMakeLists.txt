set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bassamp_tilde) # output bundle: airfx.bassamp~.mxo (_tilde->~)

target_sources(airfx.bassamp_tilde
    PRIVATE
        airfx.bassamp_tilde.cpp)

target_include_directories(airfx.bassamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bassamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
