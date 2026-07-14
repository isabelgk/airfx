set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.baxandall2_tilde) # output bundle: airfx.baxandall2~.mxo (_tilde->~)

target_sources(airfx.baxandall2_tilde
    PRIVATE
        airfx.baxandall2_tilde.cpp)

target_include_directories(airfx.baxandall2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.baxandall2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
