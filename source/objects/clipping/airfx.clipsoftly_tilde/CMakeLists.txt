set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.clipsoftly_tilde) # output bundle: airfx.clipsoftly~.mxo (_tilde->~)

target_sources(airfx.clipsoftly_tilde
    PRIVATE
        airfx.clipsoftly_tilde.cpp)

target_include_directories(airfx.clipsoftly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.clipsoftly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
