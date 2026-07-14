set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console6buss_tilde) # output bundle: airfx.console6buss~.mxo (_tilde->~)

target_sources(airfx.console6buss_tilde
    PRIVATE
        airfx.console6buss_tilde.cpp)

target_include_directories(airfx.console6buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console6buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
