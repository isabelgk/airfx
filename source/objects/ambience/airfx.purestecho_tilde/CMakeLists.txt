set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestecho_tilde) # output bundle: airfx.purestecho~.mxo (_tilde->~)

target_sources(airfx.purestecho_tilde
    PRIVATE
        airfx.purestecho_tilde.cpp)

target_include_directories(airfx.purestecho_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestecho_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
