set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplateb_tilde) # output bundle: airfx.kplateb~.mxo (_tilde->~)

target_sources(airfx.kplateb_tilde
    PRIVATE
        airfx.kplateb_tilde.cpp)

target_include_directories(airfx.kplateb_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplateb_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
