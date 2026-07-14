set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.calibre_tilde) # output bundle: airfx.calibre~.mxo (_tilde->~)

target_sources(airfx.calibre_tilde
    PRIVATE
        airfx.calibre_tilde.cpp)

target_include_directories(airfx.calibre_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.calibre_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
