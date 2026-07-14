set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.disintegrate_tilde) # output bundle: airfx.disintegrate~.mxo (_tilde->~)

target_sources(airfx.disintegrate_tilde
    PRIVATE
        airfx.disintegrate_tilde.cpp)

target_include_directories(airfx.disintegrate_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.disintegrate_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
