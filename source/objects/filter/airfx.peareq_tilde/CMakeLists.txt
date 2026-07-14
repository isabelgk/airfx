set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.peareq_tilde) # output bundle: airfx.peareq~.mxo (_tilde->~)

target_sources(airfx.peareq_tilde
    PRIVATE
        airfx.peareq_tilde.cpp)

target_include_directories(airfx.peareq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.peareq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
