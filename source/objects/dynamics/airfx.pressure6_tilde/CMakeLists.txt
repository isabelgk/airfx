set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pressure6_tilde) # output bundle: airfx.pressure6~.mxo (_tilde->~)

target_sources(airfx.pressure6_tilde
    PRIVATE
        airfx.pressure6_tilde.cpp)

target_include_directories(airfx.pressure6_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pressure6_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
