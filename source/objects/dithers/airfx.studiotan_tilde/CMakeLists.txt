set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.studiotan_tilde) # output bundle: airfx.studiotan~.mxo (_tilde->~)

target_sources(airfx.studiotan_tilde
    PRIVATE
        airfx.studiotan_tilde.cpp)

target_include_directories(airfx.studiotan_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.studiotan_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
