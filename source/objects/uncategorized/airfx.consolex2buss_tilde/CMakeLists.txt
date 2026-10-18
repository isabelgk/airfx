set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolex2buss_tilde) # output bundle: airfx.consolex2buss~.mxo (_tilde->~)

target_sources(airfx.consolex2buss_tilde
    PRIVATE
        airfx.consolex2buss_tilde.cpp)

target_include_directories(airfx.consolex2buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolex2buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
