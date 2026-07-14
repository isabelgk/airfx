set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel6_tilde) # output bundle: airfx.channel6~.mxo (_tilde->~)

target_sources(airfx.channel6_tilde
    PRIVATE
        airfx.channel6_tilde.cpp)

target_include_directories(airfx.channel6_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel6_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
