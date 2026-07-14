set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pressure5_tilde) # output bundle: airfx.pressure5~.mxo (_tilde->~)

target_sources(airfx.pressure5_tilde
    PRIVATE
        airfx.pressure5_tilde.cpp)

target_include_directories(airfx.pressure5_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pressure5_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
