set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mv_tilde) # output bundle: airfx.mv~.mxo (_tilde->~)

target_sources(airfx.mv_tilde
    PRIVATE
        airfx.mv_tilde.cpp)

target_include_directories(airfx.mv_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mv_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
