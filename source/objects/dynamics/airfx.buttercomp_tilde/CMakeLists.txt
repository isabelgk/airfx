set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.buttercomp_tilde) # output bundle: airfx.buttercomp~.mxo (_tilde->~)

target_sources(airfx.buttercomp_tilde
    PRIVATE
        airfx.buttercomp_tilde.cpp)

target_include_directories(airfx.buttercomp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.buttercomp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
