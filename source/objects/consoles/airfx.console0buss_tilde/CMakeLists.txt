set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console0buss_tilde) # output bundle: airfx.console0buss~.mxo (_tilde->~)

target_sources(airfx.console0buss_tilde
    PRIVATE
        airfx.console0buss_tilde.cpp)

target_include_directories(airfx.console0buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console0buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
