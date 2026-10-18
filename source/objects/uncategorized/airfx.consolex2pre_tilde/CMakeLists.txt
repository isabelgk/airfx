set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolex2pre_tilde) # output bundle: airfx.consolex2pre~.mxo (_tilde->~)

target_sources(airfx.consolex2pre_tilde
    PRIVATE
        airfx.consolex2pre_tilde.cpp)

target_include_directories(airfx.consolex2pre_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolex2pre_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
