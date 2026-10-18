set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolehchannel_tilde) # output bundle: airfx.consolehchannel~.mxo (_tilde->~)

target_sources(airfx.consolehchannel_tilde
    PRIVATE
        airfx.consolehchannel_tilde.cpp)

target_include_directories(airfx.consolehchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolehchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
