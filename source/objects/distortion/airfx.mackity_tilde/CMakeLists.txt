set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mackity_tilde) # output bundle: airfx.mackity~.mxo (_tilde->~)

target_sources(airfx.mackity_tilde
    PRIVATE
        airfx.mackity_tilde.cpp)

target_include_directories(airfx.mackity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mackity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
