set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kstation_tilde) # output bundle: airfx.kstation~.mxo (_tilde->~)

target_sources(airfx.kstation_tilde
    PRIVATE
        airfx.kstation_tilde.cpp)

target_include_directories(airfx.kstation_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kstation_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
