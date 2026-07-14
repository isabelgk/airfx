set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cojones_tilde) # output bundle: airfx.cojones~.mxo (_tilde->~)

target_sources(airfx.cojones_tilde
    PRIVATE
        airfx.cojones_tilde.cpp)

target_include_directories(airfx.cojones_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cojones_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
