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

json readJson(const std::string& path) {
	std::ifstream ifs(path);
	if (!ifs) throw std::runtime_error("readJson()::ファイルを開けませんでした");
	json j;
	ifs >> j;
	return j;
}


void save(json& j, Result res) {
	if (res.result == UINT64_MAX) return;
	j[res.instr][res.depends][std::to_string(res.instrNum)] = res.result;
}

void writeJsonMeta(json& j) {
	json& meta = j["meta"];
	meta["unixTime"] = static_cast<int64_t>(std::time(nullptr));
	meta["loop_in"] = LOOP_IN;
	meta["loop_out"] = LOOP_OUT;
}

void readConfig(const std::string& path, int& loopIn, int& loopOut) {
	json config = readJson(path);
	if (!config.contains("loop_in") || !config.contains("loop_out")) {
		// どちらかでも存在しない場合
		throw std::runtime_error("config json: key not found");
	} else {
		loopIn = config["loop_in"].get<int>();
		loopOut = config["loop_out"].get<int>();
	}
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
	readConfig("../config.json", LOOP_IN, LOOP_OUT);
	json j;
	writeJsonMeta(j);
	json& data = j["data"];

	// warm-up
	for (int i = 0; i < 16; i++) {
		RUN(data, add_dep)
	}

	// add
	RUN(data, add_dep);
	RUN(data, add_ind);

	// mul
	RUN(data, mul_dep);
	RUN(data, mul_ind);

	// div
	RUN(data, div_dep);
	RUN(data, div_ind);

	// sqrt
	RUN(data, sqrt_dep);
	RUN(data, sqrt_ind);

	// fma
	RUN(data, fma_dep);
	RUN(data, fma_ind);

	// load
	RUN(data, load_dep);
	RUN(data, load_ind);

	// std::cout << "j: \n" << j.dump(4);
	// std::cout << "data: \n" << data.dump(4);

	writeJson(j, "data.json");
	std::cout << "done.\n";
}
