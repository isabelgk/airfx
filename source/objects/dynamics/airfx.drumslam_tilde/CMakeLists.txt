set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.drumslam_tilde) # output bundle: airfx.drumslam~.mxo (_tilde->~)

target_sources(airfx.drumslam_tilde
    PRIVATE
        airfx.drumslam_tilde.cpp)

target_include_directories(airfx.drumslam_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.drumslam_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
