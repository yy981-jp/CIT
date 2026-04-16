#include <x86intrin.h>
#include <iostream>
#include <cstdint>
#include <algorithm>

constexpr int LOOP = 100'0000; // 100万
constexpr int REPEAT = 10;

#define GEN(NAME, INSTCOUNT, BODY) \
namespace asmImpl { \
double NAME##_##INSTCOUNT() { \
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
	return ((double)best / (double)LOOP) / (double)INSTCOUNT; \
} \
}



// 依存あり
GEN(add_dep, 1, "add rax,1\n")
GEN(add_dep, 2, "add rax,1\nadd rax,1\n")
GEN(add_dep, 4, "add rax,1\nadd rax,1\nadd rax,1\nadd rax,1\n")

// 依存なし
GEN(add_ind, 1, "add rax,1\n")
GEN(add_ind, 2, "add rax,1\nadd rbx,1\n")
GEN(add_ind, 4, "add rax,1\nadd rbx,1\nadd rcx,1\nadd rdx,1\n")
GEN(add_ind, 8, "add rax,1\nadd rbx,1\nadd rcx,1\nadd rdx,1\nadd r8,1\nadd r9,1\nadd r10,1\nadd r11,1\n")

GEN(mul_dep, 1, "imul rax,rax\n")
GEN(mul_dep, 2, "imul rax,rax\nimul rax,rax\n")
GEN(mul_dep, 4, "imul rax,rax\nimul rax,rax\nimul rax,rax\nimul rax,rax\n")

GEN(mul_ind, 1, "imul rax,rbx\n")
GEN(mul_ind, 2, "imul rax,rbx\nimul rcx,rdx\n")
GEN(mul_ind, 4, "imul rax,rbx\nimul rcx,rdx\nimul r8,r9\nimul r10,r11\n")
GEN(mul_ind, 8, "imul rax,rbx\nimul rcx,rdx\nimul r8,r9\nimul r10,r11\nimul r12,r13\nimul r14,r15\nimul rbx,rcx\nimul rdx,r8\n")

GEN(div_dep, 1,
	"mov rdx,0\n"
	"mov rax,100\n"
	"mov rbx,3\n"
	"idiv rbx\n"
)

GEN(sqrt_dep, 1, "sqrtss xmm0,xmm0\n")
GEN(sqrt_dep, 2, "sqrtss xmm0,xmm0\nsqrtss xmm0,xmm0\n")
GEN(sqrt_dep, 4, "sqrtss xmm0,xmm0\nsqrtss xmm0,xmm0\nsqrtss xmm0,xmm0\nsqrtss xmm0,xmm0\n")

GEN(sqrt_ind, 1, "sqrtss xmm0,xmm1\n")
GEN(sqrt_ind, 2, "sqrtss xmm0,xmm1\nsqrtss xmm2,xmm3\n")
GEN(sqrt_ind, 4, "sqrtss xmm0,xmm1\nsqrtss xmm2,xmm3\nsqrtss xmm4,xmm5\nsqrtss xmm6,xmm7\n")


int main() {
	std::cout << "add_dep_1 " << asmImpl::add_dep_1() << "\n";
	std::cout << "add_ind_8 " << asmImpl::add_ind_8() << "\n";

	std::cout << "mul_dep_1 " << asmImpl::mul_dep_1() << "\n";
	std::cout << "mul_ind_8 " << asmImpl::mul_ind_8() << "\n";

	std::cout << "div_dep_1 " << asmImpl::div_dep_1() << "\n";

	std::cout << "sqrt_dep_1 " << asmImpl::sqrt_dep_1() << "\n";
	std::cout << "sqrt_ind_4 " << asmImpl::sqrt_ind_4() << "\n";
}
