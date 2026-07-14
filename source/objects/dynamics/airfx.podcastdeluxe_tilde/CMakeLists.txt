set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.podcastdeluxe_tilde) # output bundle: airfx.podcastdeluxe~.mxo (_tilde->~)

target_sources(airfx.podcastdeluxe_tilde
    PRIVATE
        airfx.podcastdeluxe_tilde.cpp)

target_include_directories(airfx.podcastdeluxe_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.podcastdeluxe_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
