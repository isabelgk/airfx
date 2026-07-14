set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel8_tilde) # output bundle: airfx.channel8~.mxo (_tilde->~)

target_sources(airfx.channel8_tilde
    PRIVATE
        airfx.channel8_tilde.cpp)

target_include_directories(airfx.channel8_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel8_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
