set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolehpre_tilde) # output bundle: airfx.consolehpre~.mxo (_tilde->~)

target_sources(airfx.consolehpre_tilde
    PRIVATE
        airfx.consolehpre_tilde.cpp)

target_include_directories(airfx.consolehpre_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolehpre_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
