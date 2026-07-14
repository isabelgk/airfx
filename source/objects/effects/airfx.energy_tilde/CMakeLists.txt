set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.energy_tilde) # output bundle: airfx.energy~.mxo (_tilde->~)

target_sources(airfx.energy_tilde
    PRIVATE
        airfx.energy_tilde.cpp)

target_include_directories(airfx.energy_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.energy_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
