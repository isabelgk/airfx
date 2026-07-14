set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ncseventeen_tilde) # output bundle: airfx.ncseventeen~.mxo (_tilde->~)

target_sources(airfx.ncseventeen_tilde
    PRIVATE
        airfx.ncseventeen_tilde.cpp)

target_include_directories(airfx.ncseventeen_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ncseventeen_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
