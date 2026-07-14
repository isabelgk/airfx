set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.acceleration_tilde) # output bundle: airfx.acceleration~.mxo (_tilde->~)

target_sources(airfx.acceleration_tilde
    PRIVATE
        airfx.acceleration_tilde.cpp)

target_include_directories(airfx.acceleration_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.acceleration_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
