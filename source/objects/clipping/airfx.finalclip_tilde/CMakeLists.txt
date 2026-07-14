set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.finalclip_tilde) # output bundle: airfx.finalclip~.mxo (_tilde->~)

target_sources(airfx.finalclip_tilde
    PRIVATE
        airfx.finalclip_tilde.cpp)

target_include_directories(airfx.finalclip_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.finalclip_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
