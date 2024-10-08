
if(NOT "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitinfo.txt" IS_NEWER_THAN "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "/home/seeder/dev/thirdparty_repos/zaphoyd/websocketpp" "websocketpp-src"
    WORKING_DIRECTORY "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: '/home/seeder/dev/thirdparty_repos/zaphoyd/websocketpp'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout 56123c87598f8b1dd471be83ca841ceae07f95ba --
  WORKING_DIRECTORY "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '56123c87598f8b1dd471be83ca841ceae07f95ba'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitinfo.txt"
    "/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/root/dev_1u_new/switcher_keyboard_demmo_cc/build/_deps/websocketpp-subbuild/websocketpp-populate-prefix/src/websocketpp-populate-stamp/websocketpp-populate-gitclone-lastrun.txt'")
endif()

