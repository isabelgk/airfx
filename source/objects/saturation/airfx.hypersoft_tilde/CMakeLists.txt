set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hypersoft_tilde) # output bundle: airfx.hypersoft~.mxo (_tilde->~)

target_sources(airfx.hypersoft_tilde
    PRIVATE
        airfx.hypersoft_tilde.cpp)

target_include_directories(airfx.hypersoft_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hypersoft_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
