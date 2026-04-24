import json
import matplotlib.pyplot as plt
import sys


if len(sys.argv) > 1:
	jsonFPath = sys.argv[1]
else:
	jsonFPath = "../build/data.json"


# JSON読み込み
with open(jsonFPath, 'r', encoding='utf-8') as f:
    j = json.load(f)
    data = j["data"]


plt.rcParams['font.family'] = 'Meiryo'
plt.tight_layout()

# ===== 個別に出力 =====
for op, content in data.items():
    plt.figure()

    # dep
    if "dep" in content:
        x_dep = list(map(int, content["dep"].keys()))
        y_dep = list(content["dep"].values())
        plt.plot(x_dep, y_dep, marker='o', label="データ依存処理")

    # ind
    if "ind" in content:
        x_ind = list(map(int, content["ind"].keys()))
        y_ind = list(content["ind"].values())
        plt.plot(x_ind, y_ind, marker='o', label="独立処理")

    plt.title(op.upper())
    plt.xlabel("命令数")
    plt.ylabel("所要時間 (cycles)")
    plt.legend()
    plt.grid()

    # plt.show()
    plt.savefig(f"graphs/{op}.png", dpi=300)
    plt.close()

# ===== dep 全opまとめ =====
plt.figure()

for op, content in data.items():
    if "dep" in content:
        x = list(map(int, content["dep"].keys()))
        y = list(content["dep"].values())
        plt.plot(x, y, marker='o', label=op)

plt.title("データ依存処理")
plt.xlabel("命令数")
plt.ylabel("所要時間 (cycles)")
plt.legend()
plt.grid()

plt.savefig("graphs/_dep.png", dpi=300)
plt.close()


# ===== ind 全opまとめ =====
plt.figure()

for op, content in data.items():
    if "ind" in content:
        x = list(map(int, content["ind"].keys()))
        y = list(content["ind"].values())
        plt.plot(x, y, marker='o', label=op)

plt.title("独立処理")
plt.xlabel("命令数")
plt.ylabel("所要時間 (cycles)")
plt.legend()
plt.grid()

plt.savefig("graphs/_ind.png", dpi=300)
plt.close()
