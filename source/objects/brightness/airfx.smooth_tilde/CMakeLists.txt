set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.smooth_tilde) # output bundle: airfx.smooth~.mxo (_tilde->~)

target_sources(airfx.smooth_tilde
    PRIVATE
        airfx.smooth_tilde.cpp)

target_include_directories(airfx.smooth_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.smooth_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
