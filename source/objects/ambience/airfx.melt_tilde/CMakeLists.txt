set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.melt_tilde) # output bundle: airfx.melt~.mxo (_tilde->~)

target_sources(airfx.melt_tilde
    PRIVATE
        airfx.melt_tilde.cpp)

target_include_directories(airfx.melt_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.melt_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
