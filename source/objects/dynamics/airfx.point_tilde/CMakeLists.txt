set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.point_tilde) # output bundle: airfx.point~.mxo (_tilde->~)

target_sources(airfx.point_tilde
    PRIVATE
        airfx.point_tilde.cpp)

target_include_directories(airfx.point_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.point_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
