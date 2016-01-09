#ifndef VERILOG_ZEROALL_H
#define VERILOG_ZEROALL_H

#ifdef _MSC_VER
#define PLI_DLLESPEC __declspec(dllexport)
#else
#define PLI_DLLESPEC
#endif

#define API PLI_DLLESPEC

#endif