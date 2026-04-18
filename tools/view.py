import json
import matplotlib.pyplot as plt
from matplotlib import font_manager

# JSON読み込み
with open('../build/data.json', 'r', encoding='utf-8') as f:
    data = json.load(f)


plt.rcParams['font.family'] = 'Meiryo'

for op, content in data.items():
    plt.figure()

    # dep
    if "dep" in content:
        x_dep = list(map(int, content["dep"].keys()))
        y_dep = list(content["dep"].values())
        plt.plot(x_dep, y_dep, marker='o', label="直列処理")

    # ind
    if "ind" in content:
        x_ind = list(map(int, content["ind"].keys()))
        y_ind = list(content["ind"].values())
        plt.plot(x_ind, y_ind, marker='o', label="並列処理")

    plt.title(op.upper())
    plt.xlabel("命令数")
    plt.ylabel("所要cycle")
    plt.legend()
    plt.grid()

    # plt.show()
    plt.savefig(f"graphs/{op}.png", dpi=300)
