set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pressure4_tilde) # output bundle: airfx.pressure4~.mxo (_tilde->~)

target_sources(airfx.pressure4_tilde
    PRIVATE
        airfx.pressure4_tilde.cpp)

target_include_directories(airfx.pressure4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pressure4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
