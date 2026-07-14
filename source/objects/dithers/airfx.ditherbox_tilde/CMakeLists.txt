set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ditherbox_tilde) # output bundle: airfx.ditherbox~.mxo (_tilde->~)

target_sources(airfx.ditherbox_tilde
    PRIVATE
        airfx.ditherbox_tilde.cpp)

target_include_directories(airfx.ditherbox_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ditherbox_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
