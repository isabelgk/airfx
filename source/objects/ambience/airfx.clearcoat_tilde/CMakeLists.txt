set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.clearcoat_tilde) # output bundle: airfx.clearcoat~.mxo (_tilde->~)

target_sources(airfx.clearcoat_tilde
    PRIVATE
        airfx.clearcoat_tilde.cpp)

target_include_directories(airfx.clearcoat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.clearcoat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
