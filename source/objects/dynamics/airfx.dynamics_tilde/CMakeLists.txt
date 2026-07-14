set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dynamics_tilde) # output bundle: airfx.dynamics~.mxo (_tilde->~)

target_sources(airfx.dynamics_tilde
    PRIVATE
        airfx.dynamics_tilde.cpp)

target_include_directories(airfx.dynamics_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dynamics_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
