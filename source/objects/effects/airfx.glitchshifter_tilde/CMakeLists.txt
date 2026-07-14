set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.glitchshifter_tilde) # output bundle: airfx.glitchshifter~.mxo (_tilde->~)

target_sources(airfx.glitchshifter_tilde
    PRIVATE
        airfx.glitchshifter_tilde.cpp)

target_include_directories(airfx.glitchshifter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.glitchshifter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
