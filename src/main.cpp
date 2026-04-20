#include <fstream>
#include <functional>
#include <nlohmann/json.hpp>

#include "gen.h"

using json = nlohmann::json;


void writeJson(const json& j, const std::string& path) {
	std::ofstream ofs(path);
	if (!ofs) throw std::runtime_error("writeJson()::ファイルを開けませんでした");
	ofs << j;
}

void run(json& j, std::function<Result()> f) {
	Result res = f();
	j[res.instr][res.depends][std::to_string(res.instrNum)] = res.result;
}



int main() {
	json j;

	// add
	run(j, asmImpl::add_dep_1);
	run(j, asmImpl::add_dep_2);
	run(j, asmImpl::add_dep_3);
	run(j, asmImpl::add_dep_4);
	run(j, asmImpl::add_dep_5);
	run(j, asmImpl::add_dep_6);
	run(j, asmImpl::add_dep_7);
	run(j, asmImpl::add_dep_8);
	run(j, asmImpl::add_ind_1);
	run(j, asmImpl::add_ind_2);
	run(j, asmImpl::add_ind_3);
	run(j, asmImpl::add_ind_4);
	run(j, asmImpl::add_ind_5);
	run(j, asmImpl::add_ind_6);
	run(j, asmImpl::add_ind_7);
	run(j, asmImpl::add_ind_8);

	// mul
	run(j, asmImpl::mul_dep_1);
	run(j, asmImpl::mul_dep_2);
	run(j, asmImpl::mul_dep_3);
	run(j, asmImpl::mul_dep_4);
	run(j, asmImpl::mul_dep_5);
	run(j, asmImpl::mul_dep_6);
	run(j, asmImpl::mul_dep_7);
	run(j, asmImpl::mul_dep_8);
	run(j, asmImpl::mul_ind_1);
	run(j, asmImpl::mul_ind_2);
	run(j, asmImpl::mul_ind_3);
	run(j, asmImpl::mul_ind_4);
	run(j, asmImpl::mul_ind_5);
	run(j, asmImpl::mul_ind_6);
	run(j, asmImpl::mul_ind_7);
	run(j, asmImpl::mul_ind_8);

	// div
	run(j, asmImpl::div_dep_1);
	run(j, asmImpl::div_dep_2);
	run(j, asmImpl::div_dep_3);
	run(j, asmImpl::div_dep_4);
	run(j, asmImpl::div_dep_5);
	run(j, asmImpl::div_dep_6);
	run(j, asmImpl::div_dep_7);
	run(j, asmImpl::div_dep_8);

	// sqrt
	run(j, asmImpl::sqrt_dep_1);
	run(j, asmImpl::sqrt_dep_2);
	run(j, asmImpl::sqrt_dep_3);
	run(j, asmImpl::sqrt_dep_4);
	run(j, asmImpl::sqrt_dep_5);
	run(j, asmImpl::sqrt_dep_6);
	run(j, asmImpl::sqrt_dep_7);
	run(j, asmImpl::sqrt_dep_8);
	run(j, asmImpl::sqrt_ind_1);
	run(j, asmImpl::sqrt_ind_2);
	run(j, asmImpl::sqrt_ind_3);
	run(j, asmImpl::sqrt_ind_4);
	run(j, asmImpl::sqrt_ind_5);
	run(j, asmImpl::sqrt_ind_6);
	run(j, asmImpl::sqrt_ind_7);
	run(j, asmImpl::sqrt_ind_8);

	// fma
	run(j, asmImpl::fma_dep_1);
	run(j, asmImpl::fma_dep_2);
	run(j, asmImpl::fma_dep_3);
	run(j, asmImpl::fma_dep_4);
	run(j, asmImpl::fma_dep_5);
	run(j, asmImpl::fma_dep_6);
	run(j, asmImpl::fma_dep_7);
	run(j, asmImpl::fma_dep_8);
	run(j, asmImpl::fma_ind_1);
	run(j, asmImpl::fma_ind_2);
	run(j, asmImpl::fma_ind_3);
	run(j, asmImpl::fma_ind_4);
	run(j, asmImpl::fma_ind_5);
	run(j, asmImpl::fma_ind_6);
	run(j, asmImpl::fma_ind_7);
	run(j, asmImpl::fma_ind_8);

	// std::cout << j.dump(4);

	writeJson(j, "data.json");
}
