set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stereofx_tilde) # output bundle: airfx.stereofx~.mxo (_tilde->~)

target_sources(airfx.stereofx_tilde
    PRIVATE
        airfx.stereofx_tilde.cpp)

target_include_directories(airfx.stereofx_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stereofx_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
