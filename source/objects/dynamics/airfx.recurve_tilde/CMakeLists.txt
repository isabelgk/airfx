set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.recurve_tilde) # output bundle: airfx.recurve~.mxo (_tilde->~)

target_sources(airfx.recurve_tilde
    PRIVATE
        airfx.recurve_tilde.cpp)

target_include_directories(airfx.recurve_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.recurve_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
