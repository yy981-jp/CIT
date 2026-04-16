#include <fstream>
#include <nlohmann/json.hpp>

#include "gen.h"

using json = nlohmann::json;


json readJson(const std::string& path) {
	std::ifstream ifs(path);
	if (!ifs) throw std::runtime_error("readJson()::ファイルを開けませんでした");
	json j;
	ifs >> j;
	return j;
}

void writeJson(const json& j, const std::string& path) {
	std::ofstream ofs(path);
	if (!ofs) throw std::runtime_error("writeJson()::ファイルを開けませんでした");
	ofs << j;
}



int main() {
	json j;

	// add
	j["add"]["dep"]["1"] = asmImpl::add_dep_1();
	j["add"]["dep"]["2"] = asmImpl::add_dep_2();
	j["add"]["dep"]["3"] = asmImpl::add_dep_3();
	j["add"]["dep"]["4"] = asmImpl::add_dep_4();
	j["add"]["dep"]["5"] = asmImpl::add_dep_5();
	j["add"]["dep"]["6"] = asmImpl::add_dep_6();
	j["add"]["dep"]["7"] = asmImpl::add_dep_7();
	j["add"]["dep"]["8"] = asmImpl::add_dep_8();
	j["add"]["ind"]["1"] = asmImpl::add_ind_1();
	j["add"]["ind"]["2"] = asmImpl::add_ind_2();
	j["add"]["ind"]["3"] = asmImpl::add_ind_3();
	j["add"]["ind"]["4"] = asmImpl::add_ind_4();
	j["add"]["ind"]["5"] = asmImpl::add_ind_5();
	j["add"]["ind"]["6"] = asmImpl::add_ind_6();
	j["add"]["ind"]["7"] = asmImpl::add_ind_7();
	j["add"]["ind"]["8"] = asmImpl::add_ind_8();

	// mul
	j["mul"]["dep"]["1"] = asmImpl::mul_dep_1();
	j["mul"]["dep"]["2"] = asmImpl::mul_dep_2();
	j["mul"]["dep"]["3"] = asmImpl::mul_dep_3();
	j["mul"]["dep"]["4"] = asmImpl::mul_dep_4();
	j["mul"]["dep"]["5"] = asmImpl::mul_dep_5();
	j["mul"]["dep"]["6"] = asmImpl::mul_dep_6();
	j["mul"]["dep"]["7"] = asmImpl::mul_dep_7();
	j["mul"]["dep"]["8"] = asmImpl::mul_dep_8();
	j["mul"]["ind"]["1"] = asmImpl::mul_ind_1();
	j["mul"]["ind"]["2"] = asmImpl::mul_ind_2();
	// j["mul"]["ind"]["3"] = asmImpl::mul_ind_3();
	j["mul"]["ind"]["4"] = asmImpl::mul_ind_4();
	// j["mul"]["ind"]["5"] = asmImpl::mul_ind_5();
	// j["mul"]["ind"]["6"] = asmImpl::mul_ind_6();
	// j["mul"]["ind"]["7"] = asmImpl::mul_ind_7();
	j["mul"]["ind"]["8"] = asmImpl::mul_ind_8();

	// div
	j["div"]["dep"]["1"] = asmImpl::div_dep_1();
	j["div"]["dep"]["2"] = asmImpl::div_dep_2();
	j["div"]["dep"]["4"] = asmImpl::div_dep_4();
	j["div"]["ind"]["1"] = asmImpl::div_ind_1();
	j["div"]["ind"]["2"] = asmImpl::div_ind_2();
	j["div"]["ind"]["4"] = asmImpl::div_ind_4();
	j["div"]["ind"]["8"] = asmImpl::div_ind_8();

	// mul
	j["sqrt"]["dep"]["1"] = asmImpl::sqrt_dep_1();
	j["sqrt"]["dep"]["2"] = asmImpl::sqrt_dep_2();
	j["sqrt"]["dep"]["4"] = asmImpl::sqrt_dep_4();
	j["sqrt"]["ind"]["1"] = asmImpl::sqrt_ind_1();
	j["sqrt"]["ind"]["2"] = asmImpl::sqrt_ind_2();
	j["sqrt"]["ind"]["4"] = asmImpl::sqrt_ind_4();
	j["sqrt"]["ind"]["8"] = asmImpl::sqrt_ind_8();

	// fma
	j["fma"]["dep"]["1"] = asmImpl::fma_dep_1();
	j["fma"]["dep"]["2"] = asmImpl::fma_dep_2();
	j["fma"]["dep"]["4"] = asmImpl::fma_dep_4();
	j["fma"]["ind"]["1"] = asmImpl::fma_ind_1();
	j["fma"]["ind"]["2"] = asmImpl::fma_ind_2();
	j["fma"]["ind"]["4"] = asmImpl::fma_ind_4();
	j["fma"]["ind"]["8"] = asmImpl::fma_ind_8();

	// std::cout << j.dump(4);

	writeJson(j, "data.json");
}
