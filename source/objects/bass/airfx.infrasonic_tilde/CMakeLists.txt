set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.infrasonic_tilde) # output bundle: airfx.infrasonic~.mxo (_tilde->~)

target_sources(airfx.infrasonic_tilde
    PRIVATE
        airfx.infrasonic_tilde.cpp)

target_include_directories(airfx.infrasonic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.infrasonic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
