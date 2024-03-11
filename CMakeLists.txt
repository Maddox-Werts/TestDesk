# Version Info
cmake_minimum_required(VERSION 3.5.0)
project(TestDesk VERSION 0.1.0 LANGUAGES C CXX)
include(CTest)
enable_testing()

# Extra libraries
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Files
set(SOURCES
  src/tester/question.cpp
  src/tester/quiz.cpp

  src/interface/cli.cpp

  src/main.cpp
)

# Executable
add_executable(TestDesk ${SOURCES})

# Libraries
target_include_directories(TestDesk PRIVATE ${PROJECT_SOURCE_DIR}/inc)
target_link_directories(TestDesk PRIVATE ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(TestDesk Qt6::Core Qt6::Gui Qt6::Widgets)

# Directory
set_target_properties(TestDesk PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Compile info
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
