set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.singleendedtriode_tilde) # output bundle: airfx.singleendedtriode~.mxo (_tilde->~)

target_sources(airfx.singleendedtriode_tilde
    PRIVATE
        airfx.singleendedtriode_tilde.cpp)

target_include_directories(airfx.singleendedtriode_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.singleendedtriode_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
