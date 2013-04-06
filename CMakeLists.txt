set(CMAKE_CXX_COMPILER clang++)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(meka CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11 -fno-rtti -DBOOST_NO_TYPEID -DBOOST_NO_RTTI -I/usr/local/lib/clang/3.2/include/")

find_program(LLVM_CONFIG llvm-config)
if(NOT LLVM_CONFIG)
  message(FATAL_ERROR "llvm-config was not found, please install LLVM and Clang")
endif()

execute_process(COMMAND ${LLVM_CONFIG} --cxxflags OUTPUT_VARIABLE LLVM_COMPILE_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --ldflags  OUTPUT_VARIABLE LLVM_LINK_FLAGS    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --libs     OUTPUT_VARIABLE LLVM_LIBRARIES     OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CLANG_LIBRARIES 
-lclang
# -lclangAnalysis
# -lclangARCMigrate
# -lclangAST
-lclangASTMatchers
# -lclangBasic
# -lclangCodeGen
# -lclangDriver
# -lclangEdit
# -lclangFrontend
# -lclangFrontendTool
# -lclangLex
# -lclangParse
-lclangRewriteFrontend
-lclangRewriteCore
# -lclangSema
# -lclangSerialization
# -lclangStaticAnalyzerCheckers
# -lclangStaticAnalyzerCore
# -lclangStaticAnalyzerFrontend
-lclangTooling
)
string(REPLACE ";" " " CLANG_LIBRARIES "${CLANG_LIBRARIES}")

include_directories(include src)

file(GLOB_RECURSE MEKA_INDENT_SOURCES src/*.cpp)
add_executable(meka-indent src/refactoring-tool.cpp) #${MEKA_INDENT_SOURCES})
set_target_properties(meka-indent PROPERTIES
  COMPILE_FLAGS "${LLVM_COMPILE_FLAGS}"
  LINK_FLAGS    "${LLVM_LINK_FLAGS}"
)
target_link_libraries(meka-indent ${CLANG_LIBRARIES} ${LLVM_LIBRARIES})
