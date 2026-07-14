set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zregion_tilde) # output bundle: airfx.zregion~.mxo (_tilde->~)

target_sources(airfx.zregion_tilde
    PRIVATE
        airfx.zregion_tilde.cpp)

target_include_directories(airfx.zregion_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zregion_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
