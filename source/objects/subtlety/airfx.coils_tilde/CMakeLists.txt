set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.coils_tilde) # output bundle: airfx.coils~.mxo (_tilde->~)

target_sources(airfx.coils_tilde
    PRIVATE
        airfx.coils_tilde.cpp)

target_include_directories(airfx.coils_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.coils_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
