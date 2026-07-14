set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console7buss_tilde) # output bundle: airfx.console7buss~.mxo (_tilde->~)

target_sources(airfx.console7buss_tilde
    PRIVATE
        airfx.console7buss_tilde.cpp)

target_include_directories(airfx.console7buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console7buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
