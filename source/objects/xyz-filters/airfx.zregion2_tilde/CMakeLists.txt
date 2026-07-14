set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zregion2_tilde) # output bundle: airfx.zregion2~.mxo (_tilde->~)

target_sources(airfx.zregion2_tilde
    PRIVATE
        airfx.zregion2_tilde.cpp)

target_include_directories(airfx.zregion2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zregion2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
