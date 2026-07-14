set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.highimpact_tilde) # output bundle: airfx.highimpact~.mxo (_tilde->~)

target_sources(airfx.highimpact_tilde
    PRIVATE
        airfx.highimpact_tilde.cpp)

target_include_directories(airfx.highimpact_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.highimpact_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
