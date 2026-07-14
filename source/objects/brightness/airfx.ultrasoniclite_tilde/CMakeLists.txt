set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ultrasoniclite_tilde) # output bundle: airfx.ultrasoniclite~.mxo (_tilde->~)

target_sources(airfx.ultrasoniclite_tilde
    PRIVATE
        airfx.ultrasoniclite_tilde.cpp)

target_include_directories(airfx.ultrasoniclite_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ultrasoniclite_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
