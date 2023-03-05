project("universal_test")

find_package(UNIVERSAL CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(MTL REQUIRED)

include(CTest)

set(SCALARS
    # works
    POSIT
    FIXPNT

    # broken (does not compile anything other than the basic tests)
    EPOSIT
    EFLOAT
    CFLOAT
    AREAL
    # VALID # cannot convert back to double
    UNUM
    UNUM2 # unum2_impl instead of unum2.hpp
    LNS # cannot convert a complex into a non-complex. Universal internal error
    LNS2B # undefined reference to `sw::universal::lns2b<64u, 2u, unsigned char> sw::universal::sqrt<64u, 2u, unsigned char>(sw::universal::lns2b<64u, 2u, unsigned char> const&)'

    # does not work with my tests (but might work on its own)
    EINTEGER # block type must be one of [uint8_t, uint16_t, uint32_t]. Good to know. Eigen does not like integers though. Also, sqrt fails, but I guess that's ok.
    INTEGER # Eigen does not like integers

    # questionable (I don't know how these work, but they don't work for me)
    DECIMAL # "is not a template"
    RATIONAL # "is not a template"
    # SORN # no match for common operators. Did I mess up the template arguments?




    # FLOAT # this is a quire implementation for IEEE, not to be used on its own
    # QUIRE # this is an empty directory.. but shouldn't be used on its own anyway
)

set(TESTS
    # EIGENVALUES
    # EIGENVECTORS
    # SINGULAR_VALUES
    # SINGULAR_VECTORS_U
    # SINGULAR_VECTORS_V
    # GMRES
    # STD
    # MTL
    BASIC
)

foreach(SCALAR IN LISTS SCALARS)
    foreach(TEST IN LISTS TESTS)
        add_executable(${PROJECT_NAME}_${SCALAR}_${TEST} src/main.cxx)
        set_property(TARGET ${PROJECT_NAME}_${SCALAR}_${TEST} PROPERTY CXX_STANDARD 17)
        target_link_libraries(${PROJECT_NAME}_${SCALAR}_${TEST} universal::universal Eigen3::Eigen)
        target_include_directories(${PROJECT_NAME}_${SCALAR}_${TEST} PUBLIC include/ ${MTL_DIR})
        target_compile_definitions(${PROJECT_NAME}_${SCALAR}_${TEST} PUBLIC TEST_${SCALAR} TEST_${TEST})
        add_test(NAME ${PROJECT_NAME}_${SCALAR}_${TEST} COMMAND ${PROJECT_NAME}_${SCALAR}_${TEST})
        install(TARGETS ${PROJECT_NAME}_${SCALAR}_${TEST})
    endforeach()
endforeach()


#[[
add_executable(testing src/test.cxx)
set_property(TARGET testing PROPERTY CXX_STANDARD 17)
target_link_libraries(testing universal::universal Eigen3::Eigen)
target_include_directories(testing PUBLIC include/)
]]
