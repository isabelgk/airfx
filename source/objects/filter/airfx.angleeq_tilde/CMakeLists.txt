set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.angleeq_tilde) # output bundle: airfx.angleeq~.mxo (_tilde->~)

target_sources(airfx.angleeq_tilde
    PRIVATE
        airfx.angleeq_tilde.cpp)

target_include_directories(airfx.angleeq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.angleeq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
