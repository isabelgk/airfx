set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hull_tilde) # output bundle: airfx.hull~.mxo (_tilde->~)

target_sources(airfx.hull_tilde
    PRIVATE
        airfx.hull_tilde.cpp)

target_include_directories(airfx.hull_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hull_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
