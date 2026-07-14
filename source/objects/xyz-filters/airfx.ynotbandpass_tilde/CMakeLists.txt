set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ynotbandpass_tilde) # output bundle: airfx.ynotbandpass~.mxo (_tilde->~)

target_sources(airfx.ynotbandpass_tilde
    PRIVATE
        airfx.ynotbandpass_tilde.cpp)

target_include_directories(airfx.ynotbandpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ynotbandpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
