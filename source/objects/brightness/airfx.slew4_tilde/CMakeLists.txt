set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slew4_tilde) # output bundle: airfx.slew4~.mxo (_tilde->~)

target_sources(airfx.slew4_tilde
    PRIVATE
        airfx.slew4_tilde.cpp)

target_include_directories(airfx.slew4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slew4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
