set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolex3_tilde) # output bundle: airfx.consolex3~.mxo (_tilde->~)

target_sources(airfx.consolex3_tilde
    PRIVATE
        airfx.consolex3_tilde.cpp)

target_include_directories(airfx.consolex3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolex3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
