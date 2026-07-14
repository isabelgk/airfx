set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.desk4_tilde) # output bundle: airfx.desk4~.mxo (_tilde->~)

target_sources(airfx.desk4_tilde
    PRIVATE
        airfx.desk4_tilde.cpp)

target_include_directories(airfx.desk4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.desk4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
