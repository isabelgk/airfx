set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cstrip2_tilde) # output bundle: airfx.cstrip2~.mxo (_tilde->~)

target_sources(airfx.cstrip2_tilde
    PRIVATE
        airfx.cstrip2_tilde.cpp)

target_include_directories(airfx.cstrip2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cstrip2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
