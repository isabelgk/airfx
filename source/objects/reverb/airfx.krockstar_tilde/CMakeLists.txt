set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.krockstar_tilde) # output bundle: airfx.krockstar~.mxo (_tilde->~)

target_sources(airfx.krockstar_tilde
    PRIVATE
        airfx.krockstar_tilde.cpp)

target_include_directories(airfx.krockstar_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.krockstar_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
