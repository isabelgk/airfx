set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.noise_tilde) # output bundle: airfx.noise~.mxo (_tilde->~)

target_sources(airfx.noise_tilde
    PRIVATE
        airfx.noise_tilde.cpp)

target_include_directories(airfx.noise_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.noise_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
