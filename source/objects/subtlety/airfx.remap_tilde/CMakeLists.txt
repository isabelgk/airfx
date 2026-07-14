set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.remap_tilde) # output bundle: airfx.remap~.mxo (_tilde->~)

target_sources(airfx.remap_tilde
    PRIVATE
        airfx.remap_tilde.cpp)

target_include_directories(airfx.remap_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.remap_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
