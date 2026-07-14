set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.baxandall_tilde) # output bundle: airfx.baxandall~.mxo (_tilde->~)

target_sources(airfx.baxandall_tilde
    PRIVATE
        airfx.baxandall_tilde.cpp)

target_include_directories(airfx.baxandall_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.baxandall_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
