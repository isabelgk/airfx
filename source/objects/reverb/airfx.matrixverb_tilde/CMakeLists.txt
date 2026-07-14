set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.matrixverb_tilde) # output bundle: airfx.matrixverb~.mxo (_tilde->~)

target_sources(airfx.matrixverb_tilde
    PRIVATE
        airfx.matrixverb_tilde.cpp)

target_include_directories(airfx.matrixverb_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.matrixverb_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
