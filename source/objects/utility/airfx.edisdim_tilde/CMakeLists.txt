set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.edisdim_tilde) # output bundle: airfx.edisdim~.mxo (_tilde->~)

target_sources(airfx.edisdim_tilde
    PRIVATE
        airfx.edisdim_tilde.cpp)

target_include_directories(airfx.edisdim_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.edisdim_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
