set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel4_tilde) # output bundle: airfx.channel4~.mxo (_tilde->~)

target_sources(airfx.channel4_tilde
    PRIVATE
        airfx.channel4_tilde.cpp)

target_include_directories(airfx.channel4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
