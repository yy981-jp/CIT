#pragma once
#include <x86intrin.h>
#include <iostream>
#include <cstdint>
#include <algorithm>

constexpr int LOOP = 100'0000; // 100万
constexpr int REPEAT = 10;

#define GEN(NAME, BODY) \
namespace asmImpl { \
uint64_t NAME() { \
	uint64_t best = UINT64_MAX; \
	for (int r=0; r < REPEAT; r++) { \
		unsigned aux; \
		asm volatile("lfence" ::: "memory"); \
		uint64_t start = __rdtsc(); \
		for (int i=0; i < LOOP; i++) { \
			asm volatile( \
				".intel_syntax noprefix\n" \
				BODY \
				".att_syntax\n" \
				: \
				: \
				: "rax","rbx","rcx","rdx","r8","r9","r10","r11","r12","r13","r14","r15" \
			); \
		} \
		asm volatile("lfence" ::: "memory"); \
		uint64_t end = __rdtscp(&aux); \
		best = std::min(best, end - start); \
	} \
	return best; \
} \
}





// ===== add =====
GEN(add_dep_1,
	"add rax,1\n"
)
GEN(add_dep_2,
	"add rax,1\n"
	"add rax,1\n"
)
GEN(add_dep_4,
	"add rax,1\n"
	"add rax,1\n"
	"add rax,1\n"
	"add rax,1\n"
)

GEN(add_ind_1,
	"add rax,1\n"
)
GEN(add_ind_2,
	"add rax,1\n"
	"add rbx,1\n"
)
GEN(add_ind_4,
	"add rax,1\n"
	"add rbx,1\n"
	"add rcx,1\n"
	"add rdx,1\n"
)
GEN(add_ind_8,
	"add rax,1\n"
	"add rbx,1\n"
	"add rcx,1\n"
	"add rdx,1\n"
	"add r8,1\n"
	"add r9,1\n"
	"add r10,1\n"
	"add r11,1\n"
)


// ===== mul =====
GEN(mul_dep_1,
	"imul rax,rax\n"
)
GEN(mul_dep_2,
	"imul rax,rax\n"
	"imul rax,rax\n"
)
GEN(mul_dep_4,
	"imul rax,rax\n"
	"imul rax,rax\n"
	"imul rax,rax\n"
	"imul rax,rax\n"
)

GEN(mul_ind_1,
	"imul rax,rbx\n"
)
GEN(mul_ind_2,
	"imul rax,rbx\n"
	"imul rcx,rdx\n"
)
GEN(mul_ind_4,
	"imul rax,rbx\n"
	"imul rcx,rdx\n"
	"imul r8,r9\n"
	"imul r10,r11\n"
)
GEN(mul_ind_8,
	"imul rax,rbx\n"
	"imul rcx,rdx\n"
	"imul r8,r9\n"
	"imul r10,r11\n"
	"imul r12,r13\n"
	"imul r14,r15\n"
	"imul rbx,rcx\n"
	"imul rdx,r8\n"
)


// ===== div (double) =====
GEN(div_dep_1,
	"divsd xmm0, xmm1\n"
)
GEN(div_dep_2,
	"divsd xmm0, xmm1\n"
	"divsd xmm0, xmm1\n"
)
GEN(div_dep_4,
	"divsd xmm0, xmm1\n"
	"divsd xmm0, xmm1\n"
	"divsd xmm0, xmm1\n"
	"divsd xmm0, xmm1\n"
)

GEN(div_ind_1,
	"divsd xmm0, xmm1\n"
)
GEN(div_ind_2,
	"divsd xmm0, xmm1\n"
	"divsd xmm2, xmm3\n"
)
GEN(div_ind_4,
	"divsd xmm0, xmm1\n"
	"divsd xmm2, xmm3\n"
	"divsd xmm4, xmm5\n"
	"divsd xmm6, xmm7\n"
)
GEN(div_ind_8,
	"divsd xmm0, xmm1\n"
	"divsd xmm2, xmm3\n"
	"divsd xmm4, xmm5\n"
	"divsd xmm6, xmm7\n"
	"divsd xmm8, xmm9\n"
	"divsd xmm10, xmm11\n"
	"divsd xmm12, xmm13\n"
	"divsd xmm14, xmm15\n"
)


// ===== sqrt =====
GEN(sqrt_dep_1,
	"sqrtss xmm0,xmm0\n"
)
GEN(sqrt_dep_2,
	"sqrtss xmm0,xmm0\n"
	"sqrtss xmm0,xmm0\n"
)
GEN(sqrt_dep_4,
	"sqrtss xmm0,xmm0\n"
	"sqrtss xmm0,xmm0\n"
	"sqrtss xmm0,xmm0\n"
	"sqrtss xmm0,xmm0\n"
)

GEN(sqrt_ind_1,
	"sqrtss xmm0,xmm1\n"
)
GEN(sqrt_ind_2,
	"sqrtss xmm0,xmm1\n"
	"sqrtss xmm2,xmm3\n"
)
GEN(sqrt_ind_4,
	"sqrtss xmm0,xmm1\n"
	"sqrtss xmm2,xmm3\n"
	"sqrtss xmm4,xmm5\n"
	"sqrtss xmm6,xmm7\n"
)
GEN(sqrt_ind_8,
	"sqrtss xmm0,xmm1\n"
	"sqrtss xmm2,xmm3\n"
	"sqrtss xmm4,xmm5\n"
	"sqrtss xmm6,xmm7\n"
	"sqrtss xmm7,xmm8\n"
)


// ===== fma =====
GEN(fma_dep_1,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
)
GEN(fma_dep_2,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm0, xmm1, xmm2\n"
)
GEN(fma_dep_4,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm0, xmm1, xmm2\n"
)

GEN(fma_ind_1,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
)
GEN(fma_ind_2,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm3, xmm4, xmm5\n"
)
GEN(fma_ind_4,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm3, xmm4, xmm5\n"
	"vfmadd132ps xmm6, xmm7, xmm8\n"
	"vfmadd132ps xmm9, xmm10, xmm11\n"
)
GEN(fma_ind_8,
	"vfmadd132ps xmm0, xmm1, xmm2\n"
	"vfmadd132ps xmm3, xmm4, xmm5\n"
	"vfmadd132ps xmm6, xmm7, xmm8\n"
	"vfmadd132ps xmm9, xmm10, xmm11\n"
	"vfmadd132ps xmm12, xmm13, xmm14\n"
	"vfmadd132ps xmm15, xmm0, xmm1\n"
	"vfmadd132ps xmm2, xmm3, xmm4\n"
	"vfmadd132ps xmm5, xmm6, xmm7\n"
)
