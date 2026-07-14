set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.subtight_tilde) # output bundle: airfx.subtight~.mxo (_tilde->~)

target_sources(airfx.subtight_tilde
    PRIVATE
        airfx.subtight_tilde.cpp)

target_include_directories(airfx.subtight_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.subtight_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
