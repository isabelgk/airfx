set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.preponderant_tilde) # output bundle: airfx.preponderant~.mxo (_tilde->~)

target_sources(airfx.preponderant_tilde
    PRIVATE
        airfx.preponderant_tilde.cpp)

target_include_directories(airfx.preponderant_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.preponderant_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
