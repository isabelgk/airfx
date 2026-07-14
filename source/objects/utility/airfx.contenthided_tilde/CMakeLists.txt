set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.contenthided_tilde) # output bundle: airfx.contenthided~.mxo (_tilde->~)

target_sources(airfx.contenthided_tilde
    PRIVATE
        airfx.contenthided_tilde.cpp)

target_include_directories(airfx.contenthided_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.contenthided_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
