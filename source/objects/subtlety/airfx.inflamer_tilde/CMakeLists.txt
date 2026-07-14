set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.inflamer_tilde) # output bundle: airfx.inflamer~.mxo (_tilde->~)

target_sources(airfx.inflamer_tilde
    PRIVATE
        airfx.inflamer_tilde.cpp)

target_include_directories(airfx.inflamer_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.inflamer_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
