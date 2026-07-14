set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.spatializedither_tilde) # output bundle: airfx.spatializedither~.mxo (_tilde->~)

target_sources(airfx.spatializedither_tilde
    PRIVATE
        airfx.spatializedither_tilde.cpp)

target_include_directories(airfx.spatializedither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.spatializedither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
