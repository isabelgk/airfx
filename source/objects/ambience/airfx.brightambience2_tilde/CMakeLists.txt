set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.brightambience2_tilde) # output bundle: airfx.brightambience2~.mxo (_tilde->~)

target_sources(airfx.brightambience2_tilde
    PRIVATE
        airfx.brightambience2_tilde.cpp)

target_include_directories(airfx.brightambience2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.brightambience2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
