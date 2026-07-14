set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.orbitkick_tilde) # output bundle: airfx.orbitkick~.mxo (_tilde->~)

target_sources(airfx.orbitkick_tilde
    PRIVATE
        airfx.orbitkick_tilde.cpp)

target_include_directories(airfx.orbitkick_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.orbitkick_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
