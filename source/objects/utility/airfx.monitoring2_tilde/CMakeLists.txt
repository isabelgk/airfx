set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.monitoring2_tilde) # output bundle: airfx.monitoring2~.mxo (_tilde->~)

target_sources(airfx.monitoring2_tilde
    PRIVATE
        airfx.monitoring2_tilde.cpp)

target_include_directories(airfx.monitoring2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.monitoring2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
