set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cansaw_tilde) # output bundle: airfx.cansaw~.mxo (_tilde->~)

target_sources(airfx.cansaw_tilde
    PRIVATE
        airfx.cansaw_tilde.cpp)

target_include_directories(airfx.cansaw_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cansaw_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
