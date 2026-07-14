set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tremolo_tilde) # output bundle: airfx.tremolo~.mxo (_tilde->~)

target_sources(airfx.tremolo_tilde
    PRIVATE
        airfx.tremolo_tilde.cpp)

target_include_directories(airfx.tremolo_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tremolo_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
