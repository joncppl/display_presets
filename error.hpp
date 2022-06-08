//
// Created by joncp on 6/8/2022.
//

#pragma once

#include <exception>
#include <iostream>

#include <Windows.h>

constexpr const char* error_string(LONG err)
{
  switch (err) {
    case ERROR_SUCCESS:
      return "ERROR_SUCCESS";
    case ERROR_INVALID_PARAMETER:
      return "ERROR_INVALID_PARAMETER";
    case ERROR_NOT_SUPPORTED:
      return "ERROR_NOT_SUPPORTED";
    case ERROR_ACCESS_DENIED:
      return "ERROR_ACCESS_DENIED";
    case ERROR_GEN_FAILURE:
      return "ERROR_GEN_FAILURE";
    case ERROR_BAD_CONFIGURATION:
      return "ERROR_BAD_CONFIGURATION";
    case ERROR_INSUFFICIENT_BUFFER:
      return "ERROR_INSUFFICIENT_BUFFER";
    default:
      break;
  }
  return "UNKNOWN";
}

#define GUARD_MAIN( real_main_ ) \
static int exception_guarded_main(int argc, char* argv[]) \
{                                \
  try {                          \
    return real_main(argc, argv);\
  } catch (const std::exception& e) {                     \
    std::cerr << e.what() << '\n';                        \
    return 1;                    \
  } catch (...) {                \
    std::cerr << "An unknown exception occurred\n";       \
    return 1;                    \
  }                              \
}                                \
                                 \
static int seh_get_code(unsigned int code, unsigned int* code_ptr) \
{                                \
  *code_ptr = code;              \
  return EXCEPTION_EXECUTE_HANDLER;                       \
}                                \
                                 \
int main(int argc, char* argv[]) \
{                                \
  unsigned int code;             \
  __try {                        \
    return exception_guarded_main(argc, argv);            \
  }                              \
  __except(seh_get_code(GetExceptionCode(), &code))       \
  {                              \
    std::cerr << "SEH Exception with code: " << code << '\n';      \
    return 1;                    \
  }                              \
}