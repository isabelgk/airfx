set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.derez_tilde) # output bundle: airfx.derez~.mxo (_tilde->~)

target_sources(airfx.derez_tilde
    PRIVATE
        airfx.derez_tilde.cpp)

target_include_directories(airfx.derez_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.derez_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
