set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.creature_tilde) # output bundle: airfx.creature~.mxo (_tilde->~)

target_sources(airfx.creature_tilde
    PRIVATE
        airfx.creature_tilde.cpp)

target_include_directories(airfx.creature_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.creature_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
