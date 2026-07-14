set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8channelout_tilde) # output bundle: airfx.console8channelout~.mxo (_tilde->~)

target_sources(airfx.console8channelout_tilde
    PRIVATE
        airfx.console8channelout_tilde.cpp)

target_include_directories(airfx.console8channelout_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8channelout_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
