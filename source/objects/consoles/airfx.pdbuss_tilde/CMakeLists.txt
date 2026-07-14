set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pdbuss_tilde) # output bundle: airfx.pdbuss~.mxo (_tilde->~)

target_sources(airfx.pdbuss_tilde
    PRIVATE
        airfx.pdbuss_tilde.cpp)

target_include_directories(airfx.pdbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pdbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
