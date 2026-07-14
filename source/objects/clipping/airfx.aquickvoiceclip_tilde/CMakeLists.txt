set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.aquickvoiceclip_tilde) # output bundle: airfx.aquickvoiceclip~.mxo (_tilde->~)

target_sources(airfx.aquickvoiceclip_tilde
    PRIVATE
        airfx.aquickvoiceclip_tilde.cpp)

target_include_directories(airfx.aquickvoiceclip_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.aquickvoiceclip_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
