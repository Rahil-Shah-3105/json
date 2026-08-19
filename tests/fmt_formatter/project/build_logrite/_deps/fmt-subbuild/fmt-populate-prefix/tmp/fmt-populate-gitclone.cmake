
if(NOT "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitinfo.txt" IS_NEWER_THAN "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --depth 1 --no-single-branch --config "advice.detachedHead=false" "https://github.com/fmtlib/fmt.git" "fmt-src"
    WORKING_DIRECTORY "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/fmtlib/fmt.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout 12.2.0 --
  WORKING_DIRECTORY "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '12.2.0'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitinfo.txt"
    "/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/root/logrite/scans/r3/p4861/tests/fmt_formatter/project/build_logrite/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt'")
endif()

