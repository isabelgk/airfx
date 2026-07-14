set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.galactic_tilde) # output bundle: airfx.galactic~.mxo (_tilde->~)

target_sources(airfx.galactic_tilde
    PRIVATE
        airfx.galactic_tilde.cpp)

target_include_directories(airfx.galactic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.galactic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
