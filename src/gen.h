#pragma once
#include "def.h"
#include <x86intrin.h>
#include <iostream>
#include <cstdint>
#include <algorithm>


struct Result {
	std::string instr, depends;
	int instrNum;
	uint64_t result;
};

#define GEN(INSTR, DEP, INSTRNUM, BODY) \
namespace asmImpl { \
Result INSTR##_##DEP##_##INSTRNUM() { \
	Result res; \
	res.instr = #INSTR; \
	res.depends = #DEP; \
	res.instrNum = INSTRNUM; \
	std::vector<uint64_t> results; \
	results.resize(LOOP_OUT); \
 \
	alignas(64) static uintptr_t chase[1024]; \
	static bool init = false; \
	if (!init) { \
		for(size_t i=0;i<1023;i++) \
			chase[i]=(uintptr_t)&chase[i+1]; \
 \
		chase[1023]=(uintptr_t)&chase[0]; \
 \
		init=true; \
	} \
 \
	for (int r = 0; r < LOOP_OUT; r++) { \
		unsigned aux; \
		asm volatile("lfence" ::: "memory"); \
		uint64_t start = __rdtsc(); \
		for (int i=0; i < LOOP_IN; i++) { \
			asm volatile( \
				".intel_syntax noprefix\n" \
				BODY \
				".att_syntax\n" \
				: \
				: "S"(chase) \
				: "rax","rbx","rcx","rdx","r8","r9","r10","r11","r12","r13","r14","r15" \
			); \
		} \
		asm volatile("lfence" ::: "memory"); \
		uint64_t end = __rdtscp(&aux); \
		results[r] = end - start; \
	} \
	size_t idx = results.size() * 0.05; \
	std::nth_element(results.begin(), results.begin()+idx, results.end()); \
	res.result = results[idx]; \
	return res; \
} \
}


#define REP1(x) x
#define REP2(x) REP1(x) REP1(x)
#define REP3(x) REP2(x) REP1(x)
#define REP4(x) REP2(x) REP2(x)
#define REP5(x) REP4(x) REP1(x)
#define REP6(x) REP4(x) REP2(x)
#define REP7(x) REP6(x) REP1(x)
#define REP8(x) REP4(x) REP4(x)

#define ADD_RAX "add rax,1\n"
#define ADD_RBX "add rbx,1\n"
#define ADD_RCX "add rcx,1\n"
#define ADD_RDX "add rdx,1\n"
#define ADD_R8  "add r8,1\n"
#define ADD_R9  "add r9,1\n"
#define ADD_R10 "add r10,1\n"
#define ADD_R11 "add r11,1\n"
#define ADD_R12 "add r12,1\n"
#define ADD_R13 "add r13,1\n"

#define ADD_IND_1 ADD_RAX
#define ADD_IND_2 ADD_IND_1 ADD_RBX
#define ADD_IND_3 ADD_IND_2 ADD_RCX
#define ADD_IND_4 ADD_IND_3 ADD_RDX
#define ADD_IND_5 ADD_IND_4 ADD_R8
#define ADD_IND_6 ADD_IND_5 ADD_R9
#define ADD_IND_7 ADD_IND_6 ADD_R10
#define ADD_IND_8 ADD_IND_7 ADD_R11

#define MUL_RAX "imul rax,rbx\n"
#define MUL_RCX "imul rcx,rdx\n"
#define MUL_R8 "imul r8,r9\n"
#define MUL_R10 "imul r10,r11\n"
#define MUL_R12 "imul r12,r13\n"
#define MUL_R14 "imul r14,r15\n"
#define MUL_RBX "imul rbx,rcx\n"
#define MUL_Rdx "imul rdx,r8\n"

#define MUL_IND_1 MUL_RAX
#define MUL_IND_2 MUL_IND_1 MUL_RCX
#define MUL_IND_3 MUL_IND_2 MUL_R8
#define MUL_IND_4 MUL_IND_3 MUL_R10
#define MUL_IND_5 MUL_IND_4 MUL_R12
#define MUL_IND_6 MUL_IND_5 MUL_R14
#define MUL_IND_7 MUL_IND_6 MUL_RBX
#define MUL_IND_8 MUL_IND_7 MUL_Rdx

#define SQRT_0 "sqrtss xmm0,xmm1\n"
#define SQRT_2 "sqrtss xmm2,xmm3\n"
#define SQRT_4 "sqrtss xmm4,xmm5\n"
#define SQRT_6 "sqrtss xmm6,xmm7\n"
#define SQRT_8 "sqrtss xmm8,xmm9\n"
#define SQRT_1 "sqrtss xmm1,xmm3\n"
#define SQRT_4 "sqrtss xmm4,xmm5\n"
#define SQRT_7 "sqrtss xmm7,xmm9\n"

#define SQRT_IND_1 SQRT_0 
#define SQRT_IND_2 SQRT_IND_1 SQRT_2 
#define SQRT_IND_3 SQRT_IND_2 SQRT_4 
#define SQRT_IND_4 SQRT_IND_3 SQRT_6 
#define SQRT_IND_5 SQRT_IND_4 SQRT_8 
#define SQRT_IND_6 SQRT_IND_5 SQRT_1 
#define SQRT_IND_7 SQRT_IND_6 SQRT_4 
#define SQRT_IND_8 SQRT_IND_7 SQRT_7 

#define FMA_IND_1 "vfmadd132ps xmm0, xmm1, xmm2\n"
#define FMA_IND_2 FMA_IND_1 "vfmadd132ps xmm3, xmm4, xmm5\n"
#define FMA_IND_3 FMA_IND_2 "vfmadd132ps xmm6, xmm7, xmm8\n"
#define FMA_IND_4 FMA_IND_3 "vfmadd132ps xmm9, xmm10, xmm11\n"
#define FMA_IND_5 FMA_IND_4 "vfmadd132ps xmm12, xmm13, xmm14\n"
#define FMA_IND_6 FMA_IND_5 "vfmadd132ps xmm15, xmm0, xmm1\n"
#define FMA_IND_7 FMA_IND_6 "vfmadd132ps xmm2, xmm3, xmm4\n"
#define FMA_IND_8 FMA_IND_7 "vfmadd132ps xmm5, xmm6, xmm7\n"

#define LOAD_IND_1 "mov rax,[rsi]\n"
#define LOAD_IND_2 LOAD_IND_1 "mov rbx,[rsi+8]\n"
#define LOAD_IND_3 LOAD_IND_2 "mov rcx,[rsi+16]\n"
#define LOAD_IND_4 LOAD_IND_3 "mov rdx,[rsi+24]\n"
#define LOAD_IND_5 LOAD_IND_4 "mov r8,[rsi+32]\n"
#define LOAD_IND_6 LOAD_IND_5 "mov r9,[rsi+40]\n"
#define LOAD_IND_7 LOAD_IND_6 "mov r10,[rsi+48]\n"
#define LOAD_IND_8 LOAD_IND_7 "mov r11,[rsi+56]\n"



// ===== add =====
GEN(add, dep, 1, REP1("add rax,1\n"))
GEN(add, dep, 2, REP2("add rax,1\n"))
GEN(add, dep, 3, REP3("add rax,1\n"))
GEN(add, dep, 4, REP4("add rax,1\n"))
GEN(add, dep, 5, REP5("add rax,1\n"))
GEN(add, dep, 6, REP6("add rax,1\n"))
GEN(add, dep, 7, REP7("add rax,1\n"))
GEN(add, dep, 8, REP8("add rax,1\n"))

GEN(add, ind, 1, ADD_IND_1)
GEN(add, ind, 2, ADD_IND_2)
GEN(add, ind, 3, ADD_IND_3)
GEN(add, ind, 4, ADD_IND_4)
GEN(add, ind, 5, ADD_IND_5)
GEN(add, ind, 6, ADD_IND_6)
GEN(add, ind, 7, ADD_IND_7)
GEN(add, ind, 8, ADD_IND_8)


// ===== mul =====
GEN(mul, dep, 1, REP1("imul rax,rax\n"))
GEN(mul, dep, 2, REP2("imul rax,rax\n"))
GEN(mul, dep, 3, REP3("imul rax,rax\n"))
GEN(mul, dep, 4, REP4("imul rax,rax\n"))
GEN(mul, dep, 5, REP5("imul rax,rax\n"))
GEN(mul, dep, 6, REP6("imul rax,rax\n"))
GEN(mul, dep, 7, REP7("imul rax,rax\n"))
GEN(mul, dep, 8, REP8("imul rax,rax\n"))

GEN(mul, ind, 1, MUL_IND_1)
GEN(mul, ind, 2, MUL_IND_2)
GEN(mul, ind, 3, MUL_IND_3)
GEN(mul, ind, 4, MUL_IND_4)
GEN(mul, ind, 5, MUL_IND_5)
GEN(mul, ind, 6, MUL_IND_6)
GEN(mul, ind, 7, MUL_IND_7)
GEN(mul, ind, 8, MUL_IND_8)



// ===== div (double) =====
GEN(div, dep, 1, REP1("divsd xmm0, xmm1\n"))
GEN(div, dep, 2, REP2("divsd xmm0, xmm1\n"))
GEN(div, dep, 3, REP3("divsd xmm0, xmm1\n"))
GEN(div, dep, 4, REP4("divsd xmm0, xmm1\n"))
GEN(div, dep, 5, REP5("divsd xmm0, xmm1\n"))
GEN(div, dep, 6, REP6("divsd xmm0, xmm1\n"))
GEN(div, dep, 7, REP7("divsd xmm0, xmm1\n"))
GEN(div, dep, 8, REP8("divsd xmm0, xmm1\n"))


// ===== sqrt =====
GEN(sqrt, dep, 1, REP1("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 2, REP2("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 3, REP3("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 4, REP4("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 5, REP5("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 6, REP6("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 7, REP7("sqrtss xmm0,xmm0\n"))
GEN(sqrt, dep, 8, REP8("sqrtss xmm0,xmm0\n"))

GEN(sqrt, ind, 1, SQRT_IND_1)
GEN(sqrt, ind, 2, SQRT_IND_2)
GEN(sqrt, ind, 3, SQRT_IND_3)
GEN(sqrt, ind, 4, SQRT_IND_4)
GEN(sqrt, ind, 5, SQRT_IND_5)
GEN(sqrt, ind, 6, SQRT_IND_6)
GEN(sqrt, ind, 7, SQRT_IND_7)
GEN(sqrt, ind, 8, SQRT_IND_8)


// ===== fma =====
GEN(fma, dep, 1, REP1("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 2, REP2("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 3, REP3("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 4, REP4("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 5, REP5("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 6, REP6("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 7, REP7("vfmadd132ps xmm0, xmm1, xmm2\n"))
GEN(fma, dep, 8, REP8("vfmadd132ps xmm0, xmm1, xmm2\n"))

GEN(fma, ind, 1, FMA_IND_1)
GEN(fma, ind, 2, FMA_IND_2)
GEN(fma, ind, 3, FMA_IND_3)
GEN(fma, ind, 4, FMA_IND_4)
GEN(fma, ind, 5, FMA_IND_5)
GEN(fma, ind, 6, FMA_IND_6)
GEN(fma, ind, 7, FMA_IND_7)
GEN(fma, ind, 8, FMA_IND_8)


// ===== load =====
GEN(load, dep, 1, REP1("mov rsi,[rsi]\n"))
GEN(load, dep, 2, REP2("mov rsi,[rsi]\n"))
GEN(load, dep, 3, REP3("mov rsi,[rsi]\n"))
GEN(load, dep, 4, REP4("mov rsi,[rsi]\n"))
GEN(load, dep, 5, REP5("mov rsi,[rsi]\n"))
GEN(load, dep, 6, REP6("mov rsi,[rsi]\n"))
GEN(load, dep, 7, REP7("mov rsi,[rsi]\n"))
GEN(load, dep, 8, REP8("mov rsi,[rsi]\n"))

GEN(load, ind, 1, LOAD_IND_1)
GEN(load, ind, 2, LOAD_IND_2)
GEN(load, ind, 3, LOAD_IND_3)
GEN(load, ind, 4, LOAD_IND_4)
GEN(load, ind, 5, LOAD_IND_5)
GEN(load, ind, 6, LOAD_IND_6)
GEN(load, ind, 7, LOAD_IND_7)
GEN(load, ind, 8, LOAD_IND_8)
