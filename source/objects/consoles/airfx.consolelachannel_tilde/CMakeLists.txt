set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolelachannel_tilde) # output bundle: airfx.consolelachannel~.mxo (_tilde->~)

target_sources(airfx.consolelachannel_tilde
    PRIVATE
        airfx.consolelachannel_tilde.cpp)

target_include_directories(airfx.consolelachannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolelachannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
