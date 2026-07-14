set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sidedull_tilde) # output bundle: airfx.sidedull~.mxo (_tilde->~)

target_sources(airfx.sidedull_tilde
    PRIVATE
        airfx.sidedull_tilde.cpp)

target_include_directories(airfx.sidedull_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sidedull_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
