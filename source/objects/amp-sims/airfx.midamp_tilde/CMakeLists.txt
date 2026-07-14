set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.midamp_tilde) # output bundle: airfx.midamp~.mxo (_tilde->~)

target_sources(airfx.midamp_tilde
    PRIVATE
        airfx.midamp_tilde.cpp)

target_include_directories(airfx.midamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.midamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
