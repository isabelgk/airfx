set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channelx_tilde) # output bundle: airfx.channelx~.mxo (_tilde->~)

target_sources(airfx.channelx_tilde
    PRIVATE
        airfx.channelx_tilde.cpp)

target_include_directories(airfx.channelx_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channelx_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
