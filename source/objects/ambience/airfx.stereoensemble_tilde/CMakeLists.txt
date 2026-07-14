set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stereoensemble_tilde) # output bundle: airfx.stereoensemble~.mxo (_tilde->~)

target_sources(airfx.stereoensemble_tilde
    PRIVATE
        airfx.stereoensemble_tilde.cpp)

target_include_directories(airfx.stereoensemble_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stereoensemble_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
