include(ExternalProject)

get_target_property(FAHBENCH_OUTPUT_DIR fahbench RUNTIME_OUTPUT_DIRECTORY)
if(${WIN32})
    set(WORKUNITS_DIR "${FAHBENCH_OUTPUT_DIR}/$<CONFIG>/workunits")
else()
    set(WORKUNITS_DIR "${FAHBENCH_OUTPUT_DIR}/../share/fahbench/workunits")
endif()

ExternalProject_Add(wu-dhfr
    URL "${CMAKE_CURRENT_SOURCE_DIR}/dhfr.tar.bz2"
    URL_MD5 d79283fd8f0ab780e1990c624ba8bce3
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "${CMAKE_COMMAND}" -E copy_directory <SOURCE_DIR> "${WORKUNITS_DIR}/dhfr"
)

ExternalProject_Add(wu-dhfr-implicit
    URL "${CMAKE_CURRENT_SOURCE_DIR}/dhfr-implicit.tar.bz2"
    URL_MD5 e7e8d395523685afdc6e0d3070ae050a
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "${CMAKE_COMMAND}" -E copy_directory <SOURCE_DIR> "${WORKUNITS_DIR}/dhfr-implicit"
)

ExternalProject_Add(wu-nav
    URL "${CMAKE_CURRENT_SOURCE_DIR}/nav.tar.bz2"
    URL_MD5 15551db7d643904a0168ec49be5f7bea
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "${CMAKE_COMMAND}" -E copy_directory <SOURCE_DIR> "${WORKUNITS_DIR}/nav"
)

add_custom_target(workunits DEPENDS
    wu-dhfr
    wu-dhfr-implicit
    wu-nav
)

if(${WIN32})
install(DIRECTORY "${WORKUNITS_DIR}"  DESTINATION .)
else()
install(DIRECTORY "${WORKUNITS_DIR}"  DESTINATION share/fahbench)
endif()
