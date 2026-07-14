set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stonefire_tilde) # output bundle: airfx.stonefire~.mxo (_tilde->~)

target_sources(airfx.stonefire_tilde
    PRIVATE
        airfx.stonefire_tilde.cpp)

target_include_directories(airfx.stonefire_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stonefire_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
