set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zoom_tilde) # output bundle: airfx.zoom~.mxo (_tilde->~)

target_sources(airfx.zoom_tilde
    PRIVATE
        airfx.zoom_tilde.cpp)

target_include_directories(airfx.zoom_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zoom_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
