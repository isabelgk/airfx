set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.texturize_tilde) # output bundle: airfx.texturize~.mxo (_tilde->~)

target_sources(airfx.texturize_tilde
    PRIVATE
        airfx.texturize_tilde.cpp)

target_include_directories(airfx.texturize_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.texturize_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
