set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.highpass_tilde) # output bundle: airfx.highpass~.mxo (_tilde->~)

target_sources(airfx.highpass_tilde
    PRIVATE
        airfx.highpass_tilde.cpp)

target_include_directories(airfx.highpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.highpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
