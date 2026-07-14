set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolemdchannel_tilde) # output bundle: airfx.consolemdchannel~.mxo (_tilde->~)

target_sources(airfx.consolemdchannel_tilde
    PRIVATE
        airfx.consolemdchannel_tilde.cpp)

target_include_directories(airfx.consolemdchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolemdchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
