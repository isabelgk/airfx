set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquadstack_tilde) # output bundle: airfx.biquadstack~.mxo (_tilde->~)

target_sources(airfx.biquadstack_tilde
    PRIVATE
        airfx.biquadstack_tilde.cpp)

target_include_directories(airfx.biquadstack_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquadstack_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
