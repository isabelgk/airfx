set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.derez3_tilde) # output bundle: airfx.derez3~.mxo (_tilde->~)

target_sources(airfx.derez3_tilde
    PRIVATE
        airfx.derez3_tilde.cpp)

target_include_directories(airfx.derez3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.derez3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
