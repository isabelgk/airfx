set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.varimu_tilde) # output bundle: airfx.varimu~.mxo (_tilde->~)

target_sources(airfx.varimu_tilde
    PRIVATE
        airfx.varimu_tilde.cpp)

target_include_directories(airfx.varimu_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.varimu_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
