set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ensemble_tilde) # output bundle: airfx.ensemble~.mxo (_tilde->~)

target_sources(airfx.ensemble_tilde
    PRIVATE
        airfx.ensemble_tilde.cpp)

target_include_directories(airfx.ensemble_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ensemble_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
