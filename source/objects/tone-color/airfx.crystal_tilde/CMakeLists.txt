set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.crystal_tilde) # output bundle: airfx.crystal~.mxo (_tilde->~)

target_sources(airfx.crystal_tilde
    PRIVATE
        airfx.crystal_tilde.cpp)

target_include_directories(airfx.crystal_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.crystal_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
