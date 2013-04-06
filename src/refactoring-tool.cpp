#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Rewrite/Frontend/FrontendActions.h"
#include "clang/Frontend/FrontendActions.h"
#include "llvm/Support/CommandLine.h"

namespace {

  // static llvm::cl::opt< std::string >  build_path(llvm::cl::Positional, llvm::cl::desc("<build-path>"));
  // static llvm::cl::list< std::string > source_paths(llvm::cl::Positional, llvm::cl::desc("<source0> [... <sourceN>]"), llvm::cl::OneOrMore);

  static llvm::cl::extrahelp common_help(clang::tooling::CommonOptionsParser::HelpMessage);
  static llvm::cl::extrahelp meka_help("\nMore help text...\n");

}

struct HtmlAction : clang::HTMLPrintAction {
};

int main(int argc, char const** argv) {
  clang::tooling::CommonOptionsParser option_parser(argc, argv);

  // llvm::cl::ParseCommandLineOptions(argc, argv);

#if 0

  // clang::OwningPtr< clang::tooling::CompilationDatabase > compilation_database(clang::tooling::FixedCompilationDatabase::loadFromCommandLine(argc, argv));
  // if (!compilation_database) {
  // std::string error_message;
  // compilation_database.reset(clang::tooling::CompilationDatabase::loadFromDirectory(build_path, error_message));

  // if (!compilation_database) {
  // llvm::report_fatal_error(error_message);
  // }
  // }

  // clang::tooling::RefactoringTool  refactoring_tool(option_parser.GetCompilations(), option_parser.GetSourcePathList());
  clang::ast_matchers::MatchFinder match_finder;
  if (false) {
#else // if 0
  if (true) {
#endif // if 0
  }

  if (std::string(argv[0]) == "./meka-indent") {
    // clang::tooling::RefactoringTool refactoring_tool(option_parser.GetCompilations(), option_parser.GetSourcePathList());

    clang::tooling::ClangTool refactoring_tool(option_parser.GetCompilations(), option_parser.GetSourcePathList());
    refactoring_tool.setArgumentsAdjuster(new clang::tooling::ClangSyntaxOnlyAdjuster());

    // return refactoring_tool.run(clang::tooling::newFrontendActionFactory(&html_printer));

    return refactoring_tool.run(clang::tooling::newFrontendActionFactory< ::HtmlAction >());
  }

  return 0;
}
