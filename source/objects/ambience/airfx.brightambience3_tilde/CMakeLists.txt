set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.brightambience3_tilde) # output bundle: airfx.brightambience3~.mxo (_tilde->~)

target_sources(airfx.brightambience3_tilde
    PRIVATE
        airfx.brightambience3_tilde.cpp)

target_include_directories(airfx.brightambience3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.brightambience3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
