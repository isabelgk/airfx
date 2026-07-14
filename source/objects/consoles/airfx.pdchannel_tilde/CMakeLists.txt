set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pdchannel_tilde) # output bundle: airfx.pdchannel~.mxo (_tilde->~)

target_sources(airfx.pdchannel_tilde
    PRIVATE
        airfx.pdchannel_tilde.cpp)

target_include_directories(airfx.pdchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pdchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
