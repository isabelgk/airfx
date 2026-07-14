set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dirt_tilde) # output bundle: airfx.dirt~.mxo (_tilde->~)

target_sources(airfx.dirt_tilde
    PRIVATE
        airfx.dirt_tilde.cpp)

target_include_directories(airfx.dirt_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dirt_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
