set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dithermediskers_tilde) # output bundle: airfx.dithermediskers~.mxo (_tilde->~)

target_sources(airfx.dithermediskers_tilde
    PRIVATE
        airfx.dithermediskers_tilde.cpp)

target_include_directories(airfx.dithermediskers_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dithermediskers_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
