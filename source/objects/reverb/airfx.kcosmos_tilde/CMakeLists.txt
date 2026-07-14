set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcosmos_tilde) # output bundle: airfx.kcosmos~.mxo (_tilde->~)

target_sources(airfx.kcosmos_tilde
    PRIVATE
        airfx.kcosmos_tilde.cpp)

target_include_directories(airfx.kcosmos_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcosmos_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
