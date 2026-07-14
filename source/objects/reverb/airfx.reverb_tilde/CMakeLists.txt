set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.reverb_tilde) # output bundle: airfx.reverb~.mxo (_tilde->~)

target_sources(airfx.reverb_tilde
    PRIVATE
        airfx.reverb_tilde.cpp)

target_include_directories(airfx.reverb_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.reverb_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
