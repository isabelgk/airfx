set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolehbuss_tilde) # output bundle: airfx.consolehbuss~.mxo (_tilde->~)

target_sources(airfx.consolehbuss_tilde
    PRIVATE
        airfx.consolehbuss_tilde.cpp)

target_include_directories(airfx.consolehbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolehbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
