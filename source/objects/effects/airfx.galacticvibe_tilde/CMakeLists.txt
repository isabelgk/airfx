set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.galacticvibe_tilde) # output bundle: airfx.galacticvibe~.mxo (_tilde->~)

target_sources(airfx.galacticvibe_tilde
    PRIVATE
        airfx.galacticvibe_tilde.cpp)

target_include_directories(airfx.galacticvibe_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.galacticvibe_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
