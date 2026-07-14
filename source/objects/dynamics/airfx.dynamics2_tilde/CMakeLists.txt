set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dynamics2_tilde) # output bundle: airfx.dynamics2~.mxo (_tilde->~)

target_sources(airfx.dynamics2_tilde
    PRIVATE
        airfx.dynamics2_tilde.cpp)

target_include_directories(airfx.dynamics2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dynamics2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
