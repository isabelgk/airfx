set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.distance2_tilde) # output bundle: airfx.distance2~.mxo (_tilde->~)

target_sources(airfx.distance2_tilde
    PRIVATE
        airfx.distance2_tilde.cpp)

target_include_directories(airfx.distance2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.distance2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
