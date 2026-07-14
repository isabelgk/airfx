set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquadnonlin_tilde) # output bundle: airfx.biquadnonlin~.mxo (_tilde->~)

target_sources(airfx.biquadnonlin_tilde
    PRIVATE
        airfx.biquadnonlin_tilde.cpp)

target_include_directories(airfx.biquadnonlin_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquadnonlin_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
