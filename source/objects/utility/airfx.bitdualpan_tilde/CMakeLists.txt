set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bitdualpan_tilde) # output bundle: airfx.bitdualpan~.mxo (_tilde->~)

target_sources(airfx.bitdualpan_tilde
    PRIVATE
        airfx.bitdualpan_tilde.cpp)

target_include_directories(airfx.bitdualpan_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bitdualpan_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
