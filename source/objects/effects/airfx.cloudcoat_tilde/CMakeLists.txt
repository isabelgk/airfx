set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cloudcoat_tilde) # output bundle: airfx.cloudcoat~.mxo (_tilde->~)

target_sources(airfx.cloudcoat_tilde
    PRIVATE
        airfx.cloudcoat_tilde.cpp)

target_include_directories(airfx.cloudcoat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cloudcoat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
