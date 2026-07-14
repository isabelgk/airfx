set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console4buss_tilde) # output bundle: airfx.console4buss~.mxo (_tilde->~)

target_sources(airfx.console4buss_tilde
    PRIVATE
        airfx.console4buss_tilde.cpp)

target_include_directories(airfx.console4buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console4buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
