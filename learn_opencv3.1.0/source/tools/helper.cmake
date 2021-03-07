set(_CMAKE_CONFIGS DEBUG;RELEASE;MINSIZEREL;RELWITHDEBINFO)
set(_CMAKE_LANGS  C;CXX)

set(_HELPER_OUTPUT ${CMAKE_BINARY_DIR}/helper.log.txt)

if (NOT TODAY)
    string(TIMESTAMP _HELPER_TODAY "%Y-%m-%dT%H:%M:%S")
    file(WRITE ${_HELPER_OUTPUT} "${_HELPER_TODAY}\n")
endif()

function(help_log)
    list(JOIN ARGN ";" _OUTPUT)
    file(APPEND ${_HELPER_OUTPUT}  "${_OUTPUT}\n")
    unset(_OUTPUT)
endfunction(help_log)

function(help_log_vars LOG_TAG VAR_PREFIX)
    foreach(_VAR ${ARGN})
        if(${VAR_PREFIX}_${_VAR})
            help_log("    ${LOG_TAG}.${_VAR}: ${${VAR_PREFIX}_${_VAR}}")
        endif()
    endforeach(_VAR)
    unset(_VAR)

    if(${VAR_PREFIX}_UNPARSED_ARGUMENTS)
        help_log("    ${LOG_TAG}.???: ${${VAR_PREFIX}_UNPARSED_ARGUMENTS}")
    endif()
endfunction(help_log_vars)

# setup_cc_target(
#     <NAME>
#     [SCOPE INTERFACE|PUBLIC|PRIVATE] default scope
#     [SRCS ...]
#     [HDRS ...]
#     [INCS [BEFORE] <INTERFACE|PUBLIC|PRIVATE> ...] -I
#     [LIBS <INTERFACE|PUBLIC|PRIVATE> ...] -l
#     [DEFS <INTERFACE|PUBLIC|PRIVATE> ...] -D 
#     [COPTS [BEFORE] <INTERFACE|PUBLIC|PRIVATE> ...]
#     [LDOPTS [BEFORE] ...]
#     [PROPS ...]
#     [DEPS ...]
# )
function(setup_cc_target NAME)
    set(oneValueArgs SCOPE)
    set(multiValueArgs SRCS;HDRS;INCS;LIBS;DEFS;COPTS;LDOPTS;PROPS;DEPS;OPTIONS)
    cmake_parse_arguments(_ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    help_log_vars("${NAME}" _ARG "${oneValueArgs};${multiValueArgs}")

    if(_ARG_SRCS OR _ARG_HDRS)
        #file(GLOB _SOURCES  ${_ARG_SRCS} ${_ARG_HDRS} LIST_DIRECTORIES FALSE)
        target_sources(${NAME} PRIVATE ${_ARG_SRCS})
    endif()

    if(_ARG_INCS)
        target_include_directories(${NAME} ${_ARG_SCOPE} ${_ARG_INCS})
    endif()

    if(_ARG_COPTS)
        target_compile_options(${NAME} ${_ARG_SCOPE} ${_ARG_COPTS})
    endif()

    if(_ARG_DEFS)
        target_compile_definitions(${NAME} ${_ARG_SCOPE} ${_ARG_DEFS})
    endif()

    if(_ARG_LIBS)
        target_link_libraries(${NAME} ${_ARG_SCOPE} ${_ARG_LIBS})
    endif()

    if(_ARG_LDOPTS)
        target_link_options(${NAME} ${_ARG_SCOPE} ${_ARG_LDOPTS})
    endif()

    if(_ARG_DEPS)
        add_dependencies(${NAME} ${_ARG_DEPS})
    endif()

    if(_ARG_PROPS)
        set_target_properties(${_NAME} PROPERTIES ${_ARG_PROPS})
    endif()
endfunction(setup_cc_target)

# add_cc_library(
#     <NAME> <TYPE> # STATIC|SHARED|MODULE|OBJECT|INTERFACE
#     ...
# )
function(add_cc_library NAME TYPE)
    message("+add_cc_library ${NAME} ${TYPE}")
    help_log("add_cc_library ${NAME} ${TYPE}")
    add_library(${NAME} ${TYPE} "")
    setup_cc_target(${NAME} ${ARGN})
endfunction(add_cc_library)

# add_cc_executable(<NAME> ...)
function(add_cc_executable NAME)
    message("+add_cc_executable ${NAME}")
    help_log("add_cc_executable ${NAME}")
    add_executable(${NAME} ${TYPE} "")
    setup_cc_target(${NAME} ${ARGN})
endfunction(add_cc_executable)

# add_cc_interface(NAME ...)
function(add_cc_interface NAME)
    message("+add_cc_interface ${NAME}")
    help_log("add_cc_interface ${NAME}")
    add_library(${NAME} INTERFACE IMPORTED GLOBAL)
    setup_cc_target(${NAME} SCOPE INTERFACE ${ARGN})
endfunction(add_cc_interface)

# add imported labrary. call find_path() to find include dirs. call find_library() to find libs.
# - NO_DEFAULT_PATH
#   - NO_PACKAGE_ROOT_PATH or find_package(<PackageName>) with <PackageName>_ROOT
#   - NO_CMAKE_PATH or CMAKE_PREFIX_PATH;CMAKE_LIBRARY_PATH;CMAKE_FRAMEWORK_PATH
#   - NO_CMAKE_ENVIRONMENT_PATH or environment variables
#   - HINTS,
#   - NO_SYSTEM_ENVIRONMENT_PATH or WIN:LIB
#   - NO_CMAKE_SYSTEM_PATH or CMAKE_SYSTEM_PREFIX_PATH;CMAKE_SYSTEM_LIBRARY_PATH
#   - PATHS
#
# import_cc_library(
#   <NAME>
#   HDRS xxx.h
#   LIBS xxx
#   PATHS /opt/xxx ...
#   OPTIONS ...
# )
function(import_cc_library NAME)
    message("+import_cc_library ${NAME}")
    help_log("+import_cc_library ${NAME}")

    set(options SYSPATH)
    set(multiValueArgs HDRS LIBS PATHS OPTIONS)
    cmake_parse_arguments(_ARG "${options}" "" "${multiValueArgs}" ${ARGN})
    help_log_vars("import_inteface ${NAME}" _ARG  ${options};${multiValueArgs})

    # if (MSVC)
    #     set(_ARG_ENV_INC ENV INCLUDE)
    #     set(_ARG_ENV_LIB ENV LIB)
    # endif()

    unset(_include_dir CACHE)
    unset(_libraries)

    set(find_options ${_ARG_OPTIONS})
    if(NOT SYSPATH)
        set(find_options "${find_options} NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH")
    endif()

    # find first header
    if(_ARG_HDRS)
        foreach(_header ${_ARG_HDRS})
            unset(_include_dir CACHE)
            find_path(_include_dir NAME ${_header}  
                HINTS ${_ARG_PATHS} 
                PATH_SUFFIXES include
                ${find_options})

            help_log("  find_header.  ${_header}: ${_include_dir} ")
            if (_include_dir)
                message("  find header failed: ${_header}")
                break()
            endif()
        endforeach()

        if(NOT _include_dir)
            set(${NAME}-NOTFOUND ON)
            return()
        endif()
    endif()

    # - msvc
    #   - static .lib
    #   - shared .dll, .lib
    # - gcc
    #   - static .a
    #   - shared .so

    # find all libraries
    foreach(_libname ${_ARG_LIBS})
        unset(_library CACHE)

        find_library(_library NAME ${_libname} lib${_libname}
            HINTS ${_ARG_PATHS} 
            PATH_SUFFIXES lib bin 
            ${find_options})

        help_log("  find_library. ${_libname}: ${_library}")
        if (_library)
            list(APPEND _libraries "${_library}")
        else()
            message("  find library failed: ${_header}")

            set(${NAME}-NOTFOUND ON)
            return()
        endif()
    endforeach()

    if (_include_dir OR _libraries)
        add_library(${NAME} INTERFACE IMPORTED GLOBAL)
        setup_cc_target(${NAME} 
            SCOPE INTERFACE 
            INCS ${_include_dir} 
            LIBS ${_libraries}
        )
    endif()

    unset(_include_dir CACHE)
    unset(_library CACHE)
endfunction(import_cc_library)

# get_library_name(<VAR> <NAME> [TYPE STATIC|IMPORT|SHARED] [PREFIX override_prefix] [POSTFIX postfix])
function(get_library_name VAR NAME)
    set(options TYPE)
    set(oneValueArgs PREFIX POSTFIX)
    set(multiValueArgs )

    cmake_parse_arguments(_ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT _ARG_TYPE)
        if(MSVC)
            set(_ARG_TYPE IMPORT)
        else()
            set(_ARG_TYPE SHARED)
        endif()
    endif()

    if(NOT _ARG_PREFIX)
        set(_ARG_PREFIX "${CMAKE_${_ARG_TYPE}_LIBRARY_PREFIX}")
    endif()

    set(_ARG_NAME "${_ARG_PREFIX}${NAME}${_ARG_POSTFIX}${CMAKE_DEBUG_POSTFIX}${CMAKE_${_ARG_TYPE}_LIBRARY_SUFFIX}")
    set(${VAR} "${_ARG_NAME}" PARENT_SCOPE)

    message("get_library_name: ${VAR}: ${_ARG_NAME}")
endfunction(get_library_name)

## ----------------------------------
#  show_xxx
## ----------------------------------

# show_variables([TAG tag] [ALL] var...)
function(show_variables)
    # import: _ARG_ALL, _ARG_TAG
    cmake_parse_arguments(_ARG "ALL" "TAG" "" ${ARGN})

    foreach(_VAR ${_ARG_UNPARSED_ARGUMENTS})
        message("[${_ARG_TAG}] ${_VAR}: ${${_VAR}}")
        if(_ARG_ALL)
            foreach(_ARG_CFG ${_CMAKE_CONFIGS})
                message("[${_ARG_TAG}] ${_VAR}_${_ARG_CFG}: ${${_VAR}_${_ARG_CFG}}")
            endforeach()
        endif()
    endforeach(_VAR)
endfunction(show_variables)

if (NOT CMAKE_PROPERTY_LIST)
    execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
    STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    LIST(REMOVE_DUPLICATES CMAKE_PROPERTY_LIST)
endif()

function(show_properties tgt)
    if(NOT TARGET ${tgt})
      message("There is no target named '${tgt}'")
      return()
    endif()

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
        if(prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
            continue()
        endif()

        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
        if (propval)
            get_target_property(propval ${tgt} ${prop})
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(show_properties)

function(show_interface tgt)
    if(NOT TARGET ${tgt})
      message("There is no target named '${tgt}'")
      return()
    endif()

    set(WHITELIST EXPORT_NAME;IMPORTED;NAME;MANUALLY_ADDED_DEPENDENCIES)
    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        list(FIND WHITELIST prop prop_index)
        if(prop_index GREATER -1 OR prop MATCHES "^INTERFACE_" OR prop MATCHES "^IMPORTED_LIBNAME_")
            get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
            if (propval)
                get_target_property(propval ${tgt} ${prop})
                message ("${tgt} ${prop} = ${propval}")
            endif()
        endif()
    endforeach(prop)
endfunction(show_interface)
