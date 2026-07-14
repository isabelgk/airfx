set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestfade_tilde) # output bundle: airfx.purestfade~.mxo (_tilde->~)

target_sources(airfx.purestfade_tilde
    PRIVATE
        airfx.purestfade_tilde.cpp)

target_include_directories(airfx.purestfade_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestfade_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
