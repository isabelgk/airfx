set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console9channel_tilde) # output bundle: airfx.console9channel~.mxo (_tilde->~)

target_sources(airfx.console9channel_tilde
    PRIVATE
        airfx.console9channel_tilde.cpp)

target_include_directories(airfx.console9channel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console9channel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
