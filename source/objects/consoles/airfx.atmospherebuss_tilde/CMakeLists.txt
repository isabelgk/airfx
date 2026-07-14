set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.atmospherebuss_tilde) # output bundle: airfx.atmospherebuss~.mxo (_tilde->~)

target_sources(airfx.atmospherebuss_tilde
    PRIVATE
        airfx.atmospherebuss_tilde.cpp)

target_include_directories(airfx.atmospherebuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.atmospherebuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
