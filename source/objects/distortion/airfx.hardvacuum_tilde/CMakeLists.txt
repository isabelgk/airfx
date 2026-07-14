set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hardvacuum_tilde) # output bundle: airfx.hardvacuum~.mxo (_tilde->~)

target_sources(airfx.hardvacuum_tilde
    PRIVATE
        airfx.hardvacuum_tilde.cpp)

target_include_directories(airfx.hardvacuum_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hardvacuum_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
