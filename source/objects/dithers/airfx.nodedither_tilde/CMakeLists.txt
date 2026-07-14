set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.nodedither_tilde) # output bundle: airfx.nodedither~.mxo (_tilde->~)

target_sources(airfx.nodedither_tilde
    PRIVATE
        airfx.nodedither_tilde.cpp)

target_include_directories(airfx.nodedither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.nodedither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
