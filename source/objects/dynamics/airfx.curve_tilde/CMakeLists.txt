set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.curve_tilde) # output bundle: airfx.curve~.mxo (_tilde->~)

target_sources(airfx.curve_tilde
    PRIVATE
        airfx.curve_tilde.cpp)

target_include_directories(airfx.curve_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.curve_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
