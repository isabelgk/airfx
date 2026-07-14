set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dynamics3_tilde) # output bundle: airfx.dynamics3~.mxo (_tilde->~)

target_sources(airfx.dynamics3_tilde
    PRIVATE
        airfx.dynamics3_tilde.cpp)

target_include_directories(airfx.dynamics3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dynamics3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
