set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.distance_tilde) # output bundle: airfx.distance~.mxo (_tilde->~)

target_sources(airfx.distance_tilde
    PRIVATE
        airfx.distance_tilde.cpp)

target_include_directories(airfx.distance_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.distance_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
