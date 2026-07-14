set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.adclip9_tilde) # output bundle: airfx.adclip9~.mxo (_tilde->~)

target_sources(airfx.adclip9_tilde
    PRIVATE
        airfx.adclip9_tilde.cpp)

target_include_directories(airfx.adclip9_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.adclip9_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
