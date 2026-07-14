set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.distortion_tilde) # output bundle: airfx.distortion~.mxo (_tilde->~)

target_sources(airfx.distortion_tilde
    PRIVATE
        airfx.distortion_tilde.cpp)

target_include_directories(airfx.distortion_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.distortion_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
