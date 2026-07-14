set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console0channel_tilde) # output bundle: airfx.console0channel~.mxo (_tilde->~)

target_sources(airfx.console0channel_tilde
    PRIVATE
        airfx.console0channel_tilde.cpp)

target_include_directories(airfx.console0channel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console0channel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
