#ifndef OFFSET_H_
#define OFFSET_H_

// stack frame offset
#define FRAME_OFFSET_PC         0
#define FRAME_OFFSET_PARAM0     4
#define FRAME_OFFSET_PARAM1     8

// offset for registers of context
#define CONTEXT_OFFSET_EBX      0
#define CONTEXT_OFFSET_ESI      4
#define CONTEXT_OFFSET_EDI      8
#define CONTEXT_OFFSET_EBP      12
#define CONTEXT_OFFSET_ESP      16
#define CONTEXT_OFFSET_EIP      20

#endif // eof OFFSET_H_
