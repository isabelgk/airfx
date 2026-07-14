set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.adclip7_tilde) # output bundle: airfx.adclip7~.mxo (_tilde->~)

target_sources(airfx.adclip7_tilde
    PRIVATE
        airfx.adclip7_tilde.cpp)

target_include_directories(airfx.adclip7_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.adclip7_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
