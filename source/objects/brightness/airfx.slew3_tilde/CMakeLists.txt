set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slew3_tilde) # output bundle: airfx.slew3~.mxo (_tilde->~)

target_sources(airfx.slew3_tilde
    PRIVATE
        airfx.slew3_tilde.cpp)

target_include_directories(airfx.slew3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slew3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
