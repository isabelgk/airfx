set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.drive_tilde) # output bundle: airfx.drive~.mxo (_tilde->~)

target_sources(airfx.drive_tilde
    PRIVATE
        airfx.drive_tilde.cpp)

target_include_directories(airfx.drive_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.drive_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
