set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.nikola_tilde) # output bundle: airfx.nikola~.mxo (_tilde->~)

target_sources(airfx.nikola_tilde
    PRIVATE
        airfx.nikola_tilde.cpp)

target_include_directories(airfx.nikola_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.nikola_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
