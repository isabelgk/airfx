set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.swell_tilde) # output bundle: airfx.swell~.mxo (_tilde->~)

target_sources(airfx.swell_tilde
    PRIVATE
        airfx.swell_tilde.cpp)

target_include_directories(airfx.swell_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.swell_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
