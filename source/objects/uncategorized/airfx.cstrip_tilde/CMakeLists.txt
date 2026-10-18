set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cstrip_tilde) # output bundle: airfx.cstrip~.mxo (_tilde->~)

target_sources(airfx.cstrip_tilde
    PRIVATE
        airfx.cstrip_tilde.cpp)

target_include_directories(airfx.cstrip_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cstrip_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
