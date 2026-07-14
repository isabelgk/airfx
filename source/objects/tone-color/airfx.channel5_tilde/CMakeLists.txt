set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel5_tilde) # output bundle: airfx.channel5~.mxo (_tilde->~)

target_sources(airfx.channel5_tilde
    PRIVATE
        airfx.channel5_tilde.cpp)

target_include_directories(airfx.channel5_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel5_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
