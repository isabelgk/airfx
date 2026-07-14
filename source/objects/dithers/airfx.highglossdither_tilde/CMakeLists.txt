set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.highglossdither_tilde) # output bundle: airfx.highglossdither~.mxo (_tilde->~)

target_sources(airfx.highglossdither_tilde
    PRIVATE
        airfx.highglossdither_tilde.cpp)

target_include_directories(airfx.highglossdither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.highglossdither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
