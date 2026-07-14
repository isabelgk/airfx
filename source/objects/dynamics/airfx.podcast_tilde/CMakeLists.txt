set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.podcast_tilde) # output bundle: airfx.podcast~.mxo (_tilde->~)

target_sources(airfx.podcast_tilde
    PRIVATE
        airfx.podcast_tilde.cpp)

target_include_directories(airfx.podcast_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.podcast_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
