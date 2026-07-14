set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.brightambience_tilde) # output bundle: airfx.brightambience~.mxo (_tilde->~)

target_sources(airfx.brightambience_tilde
    PRIVATE
        airfx.brightambience_tilde.cpp)

target_include_directories(airfx.brightambience_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.brightambience_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
