set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.xregion_tilde) # output bundle: airfx.xregion~.mxo (_tilde->~)

target_sources(airfx.xregion_tilde
    PRIVATE
        airfx.xregion_tilde.cpp)

target_include_directories(airfx.xregion_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.xregion_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
