import json
import matplotlib.pyplot as plt

# JSON読み込み
with open('../build/data.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# plt.style.use("gray_background")
for op, content in data.items():
    plt.figure()

    # dep
    x_dep = list(map(int, content["dep"].keys()))
    y_dep = list(content["dep"].values())

    # ind
    x_ind = list(map(int, content["ind"].keys()))
    y_ind = list(content["ind"].values())

    plt.plot(x_dep, y_dep, marker='o', label="dep")
    plt.plot(x_ind, y_ind, marker='o', label="ind")

    plt.title(op.upper())
    plt.xlabel("parallelism")
    plt.ylabel("value")
    plt.legend()
    plt.grid()

    # plt.show()
    plt.savefig(f"{op}.png", dpi=300)
