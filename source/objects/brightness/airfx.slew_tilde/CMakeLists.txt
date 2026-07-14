set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slew_tilde) # output bundle: airfx.slew~.mxo (_tilde->~)

target_sources(airfx.slew_tilde
    PRIVATE
        airfx.slew_tilde.cpp)

target_include_directories(airfx.slew_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slew_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
