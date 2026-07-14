set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.galactic3_tilde) # output bundle: airfx.galactic3~.mxo (_tilde->~)

target_sources(airfx.galactic3_tilde
    PRIVATE
        airfx.galactic3_tilde.cpp)

target_include_directories(airfx.galactic3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.galactic3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
