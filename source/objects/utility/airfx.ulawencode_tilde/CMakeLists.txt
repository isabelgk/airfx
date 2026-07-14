set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ulawencode_tilde) # output bundle: airfx.ulawencode~.mxo (_tilde->~)

target_sources(airfx.ulawencode_tilde
    PRIVATE
        airfx.ulawencode_tilde.cpp)

target_include_directories(airfx.ulawencode_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ulawencode_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
