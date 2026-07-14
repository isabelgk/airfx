set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.holt_tilde) # output bundle: airfx.holt~.mxo (_tilde->~)

target_sources(airfx.holt_tilde
    PRIVATE
        airfx.holt_tilde.cpp)

target_include_directories(airfx.holt_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.holt_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
