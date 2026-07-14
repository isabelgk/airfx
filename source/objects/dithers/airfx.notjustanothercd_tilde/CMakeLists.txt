set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.notjustanothercd_tilde) # output bundle: airfx.notjustanothercd~.mxo (_tilde->~)

target_sources(airfx.notjustanothercd_tilde
    PRIVATE
        airfx.notjustanothercd_tilde.cpp)

target_include_directories(airfx.notjustanothercd_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.notjustanothercd_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
