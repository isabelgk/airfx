set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.peaksonly_tilde) # output bundle: airfx.peaksonly~.mxo (_tilde->~)

target_sources(airfx.peaksonly_tilde
    PRIVATE
        airfx.peaksonly_tilde.cpp)

target_include_directories(airfx.peaksonly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.peaksonly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
