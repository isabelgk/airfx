set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.edge_tilde) # output bundle: airfx.edge~.mxo (_tilde->~)

target_sources(airfx.edge_tilde
    PRIVATE
        airfx.edge_tilde.cpp)

target_include_directories(airfx.edge_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.edge_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
