set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.air_tilde) # output bundle: airfx.air~.mxo (_tilde->~)

target_sources(airfx.air_tilde
    PRIVATE
        airfx.air_tilde.cpp)

target_include_directories(airfx.air_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.air_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
