set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.c5rawchannel_tilde) # output bundle: airfx.c5rawchannel~.mxo (_tilde->~)

target_sources(airfx.c5rawchannel_tilde
    PRIVATE
        airfx.c5rawchannel_tilde.cpp)

target_include_directories(airfx.c5rawchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.c5rawchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
