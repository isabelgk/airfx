set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.shape_tilde) # output bundle: airfx.shape~.mxo (_tilde->~)

target_sources(airfx.shape_tilde
    PRIVATE
        airfx.shape_tilde.cpp)

target_include_directories(airfx.shape_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.shape_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
