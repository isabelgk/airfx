set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.onecornerclip_tilde) # output bundle: airfx.onecornerclip~.mxo (_tilde->~)

target_sources(airfx.onecornerclip_tilde
    PRIVATE
        airfx.onecornerclip_tilde.cpp)

target_include_directories(airfx.onecornerclip_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.onecornerclip_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
