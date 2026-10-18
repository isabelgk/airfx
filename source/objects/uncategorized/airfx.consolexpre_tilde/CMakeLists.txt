set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolexpre_tilde) # output bundle: airfx.consolexpre~.mxo (_tilde->~)

target_sources(airfx.consolexpre_tilde
    PRIVATE
        airfx.consolexpre_tilde.cpp)

target_include_directories(airfx.consolexpre_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolexpre_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
