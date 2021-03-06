if(UNIX)
  set(CMAKE_MODULE_PATH "/usr/share/cmake-3.10/Modules")
  set(SPHINX_DIR = "/usr/bin")
endif(UNIX)

find_package(Sphinx)
if(NOT DEFINED SPHINX_THEME)
  set(SPHINX_THEME default)
endif()

if(NOT DEFINED SPHINX_THEME_DIR)
  set(SPHINX_THEME_DIR)
endif()
if (WIN32)
  if(NOT DEFINED CATAP_LOCATION)
    set(CATAP_LOCATION ${CMAKE_BINARY_DIR}/PythonInterface/Release)
  endif()
endif(WIN32)

if (UNIX)
  if(NOT DEFINED CATAP_LOCATION)
    set(CATAP_LOCATION ${CMAKE_BINARY_DIR}/PythonInterface/)
  endif()
endif(UNIX)


set(BINARY_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/_build)

set(SPHINX_CACHE_DIR ${CMAKE_CURRENT_BINARY_DIR}/_doctrees)

set(SPHINX_HTML_DIR ${CMAKE_CURRENT_BINARY_DIR}/html)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
               ${BINARY_BUILD_DIR}/conf.py
               @ONLY)

add_custom_target(CATAPPyDocs ALL
${SPHINX_EXECUTABLE} -q -b html -c ${BINARY_BUILD_DIR} -d ${SPHINX_CACHE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${SPHINX_HTML_DIR} COMMENT "Building HTML docs with Sphinx")
