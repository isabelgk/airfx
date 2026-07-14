set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.monitoring3_tilde) # output bundle: airfx.monitoring3~.mxo (_tilde->~)

target_sources(airfx.monitoring3_tilde
    PRIVATE
        airfx.monitoring3_tilde.cpp)

target_include_directories(airfx.monitoring3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.monitoring3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
