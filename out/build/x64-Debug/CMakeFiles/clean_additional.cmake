# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LoTI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LoTI_autogen.dir\\ParseCache.txt"
  "LoTI_autogen"
  )
endif()
