
add_library(argus-lib
  CommandParser.cpp
  CommandParser.h
  CommandProcessor.cpp
  CommandProcessor.h
  Command.cpp
  Command.h
  CommonTypes.h)

target_include_directories(argus-lib PUBLIC . ${ImageMagick_INCLUDE_DIRS})

target_link_libraries(argus-lib ${ImageMagick_LIBRARIES} rozhkovdmitrii)