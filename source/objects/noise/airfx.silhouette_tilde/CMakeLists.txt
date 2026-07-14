set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.silhouette_tilde) # output bundle: airfx.silhouette~.mxo (_tilde->~)

target_sources(airfx.silhouette_tilde
    PRIVATE
        airfx.silhouette_tilde.cpp)

target_include_directories(airfx.silhouette_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.silhouette_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
