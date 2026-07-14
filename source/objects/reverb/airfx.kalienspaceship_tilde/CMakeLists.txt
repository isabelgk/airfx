set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kalienspaceship_tilde) # output bundle: airfx.kalienspaceship~.mxo (_tilde->~)

target_sources(airfx.kalienspaceship_tilde
    PRIVATE
        airfx.kalienspaceship_tilde.cpp)

target_include_directories(airfx.kalienspaceship_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kalienspaceship_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
