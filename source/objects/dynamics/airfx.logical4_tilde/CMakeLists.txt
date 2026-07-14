set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.logical4_tilde) # output bundle: airfx.logical4~.mxo (_tilde->~)

target_sources(airfx.logical4_tilde
    PRIVATE
        airfx.logical4_tilde.cpp)

target_include_directories(airfx.logical4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.logical4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
