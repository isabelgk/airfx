set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.adt_tilde) # output bundle: airfx.adt~.mxo (_tilde->~)

target_sources(airfx.adt_tilde
    PRIVATE
        airfx.adt_tilde.cpp)

target_include_directories(airfx.adt_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.adt_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
