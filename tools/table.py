import json
import pandas as pd
import sys
import matplotlib.pyplot as plt
from PyQt6.QtWidgets import QApplication, QTableWidget, QTableWidgetItem


if len(sys.argv) > 1:
	jsonFPath = sys.argv[1]
else:
	jsonFPath = "../build/data.json"


# JSON読み込み
with open(jsonFPath, 'r', encoding='utf-8') as f:
    j = json.load(f)
    data = j["data"]

rows = []

for op, op_data in data.items():
	for typ, typ_data in op_data.items():  # dep / ind
		for num, value in typ_data.items():
			rows.append({
				"op": op,
				"type": typ,
				"num": int(num),
				"value": value
			})

df = pd.DataFrame(rows)

# 並び替え（見やすく）
df = df.sort_values(["op", "type", "num"])

pivot = df.pivot(index=["op", "type"], columns="num", values="value")
pivot.index = [f"{op.upper()} - {typ.upper()}" for op, typ in pivot.index]
# print(pivot)





fig, ax = plt.subplots(figsize=(8, 4))  # 横長にする
ax.axis('off')

table = ax.table(
	cellText=pivot.round(2).values,
	rowLabels=pivot.index,
	colLabels=pivot.columns,
	loc='center',
	cellLoc='center'
)

# フォントサイズ調整
table.auto_set_font_size(False)
table.set_fontsize(10)

# セルサイズ調整
table.scale(1.2, 1.5)

# ヘッダ行を強調
for (row, col), cell in table.get_celld().items():
	if row == 0:
		cell.set_text_props(weight='bold')
		cell.set_facecolor('#dddddd')

	if row > 0:
		label = pivot.index[row - 1]

		if "DEP" in label:
			cell.set_facecolor("#f0f6ff")
		elif "IND" in label:
			cell.set_facecolor("#fff0f0")

# 保存
plt.savefig("graphs/_table.png", bbox_inches='tight', dpi=300)
plt.close()
