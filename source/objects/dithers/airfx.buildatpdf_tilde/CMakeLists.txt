set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.buildatpdf_tilde) # output bundle: airfx.buildatpdf~.mxo (_tilde->~)

target_sources(airfx.buildatpdf_tilde
    PRIVATE
        airfx.buildatpdf_tilde.cpp)

target_include_directories(airfx.buildatpdf_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.buildatpdf_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
