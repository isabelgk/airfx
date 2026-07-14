set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slew2_tilde) # output bundle: airfx.slew2~.mxo (_tilde->~)

target_sources(airfx.slew2_tilde
    PRIVATE
        airfx.slew2_tilde.cpp)

target_include_directories(airfx.slew2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slew2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
