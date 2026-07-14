set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.voicetrick_tilde) # output bundle: airfx.voicetrick~.mxo (_tilde->~)

target_sources(airfx.voicetrick_tilde
    PRIVATE
        airfx.voicetrick_tilde.cpp)

target_include_directories(airfx.voicetrick_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.voicetrick_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
