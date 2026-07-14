set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapefat_tilde) # output bundle: airfx.tapefat~.mxo (_tilde->~)

target_sources(airfx.tapefat_tilde
    PRIVATE
        airfx.tapefat_tilde.cpp)

target_include_directories(airfx.tapefat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapefat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
