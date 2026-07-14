set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbthic_tilde) # output bundle: airfx.verbthic~.mxo (_tilde->~)

target_sources(airfx.verbthic_tilde
    PRIVATE
        airfx.verbthic_tilde.cpp)

target_include_directories(airfx.verbthic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbthic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
