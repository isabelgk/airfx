set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bezicomp_tilde) # output bundle: airfx.bezicomp~.mxo (_tilde->~)

target_sources(airfx.bezicomp_tilde
    PRIVATE
        airfx.bezicomp_tilde.cpp)

target_include_directories(airfx.bezicomp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bezicomp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
