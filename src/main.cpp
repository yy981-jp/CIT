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

void save(json& j, Result res) {
	j[res.instr][res.depends][std::to_string(res.instrNum)] = res.result;
}

#define RUN(J, TARGET) \
	save(J, asmImpl::TARGET##_1()); \
	save(J, asmImpl::TARGET##_2()); \
	save(J, asmImpl::TARGET##_3()); \
	save(J, asmImpl::TARGET##_4()); \
	save(J, asmImpl::TARGET##_5()); \
	save(J, asmImpl::TARGET##_6()); \
	save(J, asmImpl::TARGET##_7()); \
	save(J, asmImpl::TARGET##_8());



int main() {
	json j;

	// warm-up
	RUN(j, add_dep)

	// add
	RUN(j, add_dep);
	RUN(j, add_ind);

	// mul
	RUN(j, mul_dep);
	RUN(j, mul_ind);

	// div
	RUN(j, div_dep);

	// sqrt
	RUN(j, sqrt_dep);
	RUN(j, sqrt_ind);

	// fma
	RUN(j, fma_dep);
	RUN(j, fma_ind);

	// load
	RUN(j, load_dep);
	RUN(j, load_ind);

	// std::cout << j.dump(4);

	writeJson(j, "data.json");
	std::cout << "done.\n";
}
