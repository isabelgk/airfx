set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.triplespread_tilde) # output bundle: airfx.triplespread~.mxo (_tilde->~)

target_sources(airfx.triplespread_tilde
    PRIVATE
        airfx.triplespread_tilde.cpp)

target_include_directories(airfx.triplespread_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.triplespread_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
