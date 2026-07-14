set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.derez4_tilde) # output bundle: airfx.derez4~.mxo (_tilde->~)

target_sources(airfx.derez4_tilde
    PRIVATE
        airfx.derez4_tilde.cpp)

target_include_directories(airfx.derez4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.derez4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
