set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquad_tilde) # output bundle: airfx.biquad~.mxo (_tilde->~)

target_sources(airfx.biquad_tilde
    PRIVATE
        airfx.biquad_tilde.cpp)

target_include_directories(airfx.biquad_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquad_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
