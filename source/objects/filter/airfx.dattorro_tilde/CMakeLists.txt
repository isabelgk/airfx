set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dattorro_tilde) # output bundle: airfx.dattorro~.mxo (_tilde->~)

target_sources(airfx.dattorro_tilde
    PRIVATE
        airfx.dattorro_tilde.cpp)

target_include_directories(airfx.dattorro_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dattorro_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
