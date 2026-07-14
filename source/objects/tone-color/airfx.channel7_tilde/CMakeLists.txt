set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel7_tilde) # output bundle: airfx.channel7~.mxo (_tilde->~)

target_sources(airfx.channel7_tilde
    PRIVATE
        airfx.channel7_tilde.cpp)

target_include_directories(airfx.channel7_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel7_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
