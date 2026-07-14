set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.aura_tilde) # output bundle: airfx.aura~.mxo (_tilde->~)

target_sources(airfx.aura_tilde
    PRIVATE
        airfx.aura_tilde.cpp)

target_include_directories(airfx.aura_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.aura_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
