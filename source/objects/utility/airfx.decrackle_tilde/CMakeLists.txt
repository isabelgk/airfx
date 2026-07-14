set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.decrackle_tilde) # output bundle: airfx.decrackle~.mxo (_tilde->~)

target_sources(airfx.decrackle_tilde
    PRIVATE
        airfx.decrackle_tilde.cpp)

target_include_directories(airfx.decrackle_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.decrackle_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
