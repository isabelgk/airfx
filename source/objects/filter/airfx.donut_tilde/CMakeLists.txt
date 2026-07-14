set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.donut_tilde) # output bundle: airfx.donut~.mxo (_tilde->~)

target_sources(airfx.donut_tilde
    PRIVATE
        airfx.donut_tilde.cpp)

target_include_directories(airfx.donut_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.donut_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
