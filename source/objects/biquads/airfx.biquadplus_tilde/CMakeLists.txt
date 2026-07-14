set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquadplus_tilde) # output bundle: airfx.biquadplus~.mxo (_tilde->~)

target_sources(airfx.biquadplus_tilde
    PRIVATE
        airfx.biquadplus_tilde.cpp)

target_include_directories(airfx.biquadplus_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquadplus_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
