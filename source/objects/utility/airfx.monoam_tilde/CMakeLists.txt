set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.monoam_tilde) # output bundle: airfx.monoam~.mxo (_tilde->~)

target_sources(airfx.monoam_tilde
    PRIVATE
        airfx.monoam_tilde.cpp)

target_include_directories(airfx.monoam_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.monoam_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
