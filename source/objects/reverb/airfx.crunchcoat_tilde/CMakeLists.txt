set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.crunchcoat_tilde) # output bundle: airfx.crunchcoat~.mxo (_tilde->~)

target_sources(airfx.crunchcoat_tilde
    PRIVATE
        airfx.crunchcoat_tilde.cpp)

target_include_directories(airfx.crunchcoat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.crunchcoat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
