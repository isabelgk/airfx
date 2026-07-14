set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.acceleration2_tilde) # output bundle: airfx.acceleration2~.mxo (_tilde->~)

target_sources(airfx.acceleration2_tilde
    PRIVATE
        airfx.acceleration2_tilde.cpp)

target_include_directories(airfx.acceleration2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.acceleration2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
