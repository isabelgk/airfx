set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.monitoring_tilde) # output bundle: airfx.monitoring~.mxo (_tilde->~)

target_sources(airfx.monitoring_tilde
    PRIVATE
        airfx.monitoring_tilde.cpp)

target_include_directories(airfx.monitoring_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.monitoring_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
