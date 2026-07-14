set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.surgetide_tilde) # output bundle: airfx.surgetide~.mxo (_tilde->~)

target_sources(airfx.surgetide_tilde
    PRIVATE
        airfx.surgetide_tilde.cpp)

target_include_directories(airfx.surgetide_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.surgetide_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
