set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.grindamp_tilde) # output bundle: airfx.grindamp~.mxo (_tilde->~)

target_sources(airfx.grindamp_tilde
    PRIVATE
        airfx.grindamp_tilde.cpp)

target_include_directories(airfx.grindamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.grindamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
