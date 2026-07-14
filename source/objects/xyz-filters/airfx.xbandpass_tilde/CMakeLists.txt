set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.xbandpass_tilde) # output bundle: airfx.xbandpass~.mxo (_tilde->~)

target_sources(airfx.xbandpass_tilde
    PRIVATE
        airfx.xbandpass_tilde.cpp)

target_include_directories(airfx.xbandpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.xbandpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
