set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.baxandall3_tilde) # output bundle: airfx.baxandall3~.mxo (_tilde->~)

target_sources(airfx.baxandall3_tilde
    PRIVATE
        airfx.baxandall3_tilde.cpp)

target_include_directories(airfx.baxandall3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.baxandall3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
