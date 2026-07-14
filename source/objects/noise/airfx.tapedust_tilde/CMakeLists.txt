set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapedust_tilde) # output bundle: airfx.tapedust~.mxo (_tilde->~)

target_sources(airfx.tapedust_tilde
    PRIVATE
        airfx.tapedust_tilde.cpp)

target_include_directories(airfx.tapedust_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapedust_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
