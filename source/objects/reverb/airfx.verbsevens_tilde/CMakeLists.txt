set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbsevens_tilde) # output bundle: airfx.verbsevens~.mxo (_tilde->~)

target_sources(airfx.verbsevens_tilde
    PRIVATE
        airfx.verbsevens_tilde.cpp)

target_include_directories(airfx.verbsevens_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbsevens_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
