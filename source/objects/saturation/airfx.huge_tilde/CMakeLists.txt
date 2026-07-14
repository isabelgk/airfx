set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.huge_tilde) # output bundle: airfx.huge~.mxo (_tilde->~)

target_sources(airfx.huge_tilde
    PRIVATE
        airfx.huge_tilde.cpp)

target_include_directories(airfx.huge_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.huge_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
