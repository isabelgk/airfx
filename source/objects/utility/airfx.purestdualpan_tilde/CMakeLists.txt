set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestdualpan_tilde) # output bundle: airfx.purestdualpan~.mxo (_tilde->~)

target_sources(airfx.purestdualpan_tilde
    PRIVATE
        airfx.purestdualpan_tilde.cpp)

target_include_directories(airfx.purestdualpan_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestdualpan_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
