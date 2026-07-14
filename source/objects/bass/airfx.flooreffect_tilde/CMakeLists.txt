set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.flooreffect_tilde) # output bundle: airfx.flooreffect~.mxo (_tilde->~)

target_sources(airfx.flooreffect_tilde
    PRIVATE
        airfx.flooreffect_tilde.cpp)

target_include_directories(airfx.flooreffect_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.flooreffect_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
