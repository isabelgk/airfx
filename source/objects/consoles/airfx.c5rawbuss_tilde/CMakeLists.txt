set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.c5rawbuss_tilde) # output bundle: airfx.c5rawbuss~.mxo (_tilde->~)

target_sources(airfx.c5rawbuss_tilde
    PRIVATE
        airfx.c5rawbuss_tilde.cpp)

target_include_directories(airfx.c5rawbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.c5rawbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
