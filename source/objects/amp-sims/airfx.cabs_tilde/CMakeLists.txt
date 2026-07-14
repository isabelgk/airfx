set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cabs_tilde) # output bundle: airfx.cabs~.mxo (_tilde->~)

target_sources(airfx.cabs_tilde
    PRIVATE
        airfx.cabs_tilde.cpp)

target_include_directories(airfx.cabs_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cabs_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
