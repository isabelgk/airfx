set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lowpass_tilde) # output bundle: airfx.lowpass~.mxo (_tilde->~)

target_sources(airfx.lowpass_tilde
    PRIVATE
        airfx.lowpass_tilde.cpp)

target_include_directories(airfx.lowpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lowpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
