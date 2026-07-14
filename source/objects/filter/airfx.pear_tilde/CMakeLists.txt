set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pear_tilde) # output bundle: airfx.pear~.mxo (_tilde->~)

target_sources(airfx.pear_tilde
    PRIVATE
        airfx.pear_tilde.cpp)

target_include_directories(airfx.pear_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pear_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
