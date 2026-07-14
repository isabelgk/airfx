set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.surge_tilde) # output bundle: airfx.surge~.mxo (_tilde->~)

target_sources(airfx.surge_tilde
    PRIVATE
        airfx.surge_tilde.cpp)

target_include_directories(airfx.surge_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.surge_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
