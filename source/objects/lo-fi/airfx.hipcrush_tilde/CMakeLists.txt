set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hipcrush_tilde) # output bundle: airfx.hipcrush~.mxo (_tilde->~)

target_sources(airfx.hipcrush_tilde
    PRIVATE
        airfx.hipcrush_tilde.cpp)

target_include_directories(airfx.hipcrush_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hipcrush_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
