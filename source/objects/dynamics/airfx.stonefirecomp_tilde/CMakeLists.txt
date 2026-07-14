set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stonefirecomp_tilde) # output bundle: airfx.stonefirecomp~.mxo (_tilde->~)

target_sources(airfx.stonefirecomp_tilde
    PRIVATE
        airfx.stonefirecomp_tilde.cpp)

target_include_directories(airfx.stonefirecomp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stonefirecomp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
