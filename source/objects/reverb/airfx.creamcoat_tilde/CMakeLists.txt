set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.creamcoat_tilde) # output bundle: airfx.creamcoat~.mxo (_tilde->~)

target_sources(airfx.creamcoat_tilde
    PRIVATE
        airfx.creamcoat_tilde.cpp)

target_include_directories(airfx.creamcoat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.creamcoat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
