set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.squareroot_tilde) # output bundle: airfx.squareroot~.mxo (_tilde->~)

target_sources(airfx.squareroot_tilde
    PRIVATE
        airfx.squareroot_tilde.cpp)

target_include_directories(airfx.squareroot_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.squareroot_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
