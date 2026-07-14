set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ultrasonic_tilde) # output bundle: airfx.ultrasonic~.mxo (_tilde->~)

target_sources(airfx.ultrasonic_tilde
    PRIVATE
        airfx.ultrasonic_tilde.cpp)

target_include_directories(airfx.ultrasonic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ultrasonic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
