set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.flipity_tilde) # output bundle: airfx.flipity~.mxo (_tilde->~)

target_sources(airfx.flipity_tilde
    PRIVATE
        airfx.flipity_tilde.cpp)

target_include_directories(airfx.flipity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.flipity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
