set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.denoise_tilde) # output bundle: airfx.denoise~.mxo (_tilde->~)

target_sources(airfx.denoise_tilde
    PRIVATE
        airfx.denoise_tilde.cpp)

target_include_directories(airfx.denoise_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.denoise_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
