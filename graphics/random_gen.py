import random
from matplotlib import pyplot as plt
from matplotlib import colors

# 2mm per voxel
rows = 12 * 5
cols = 39 * 5

array = [[0 for x in range(cols)] for y in range(rows)] 

for row in range(rows):
	for col in range(cols):
		array[row][col] = random.randint(0,1)

for i in range(rows):
	print(array[i])

cmap = colors.ListedColormap(['Black','White'])
plt.figure(figsize=(cols,rows))
plt.axis("off")
plt.pcolor(array[::-1],cmap=cmap,edgecolors='', linewidths=1)
plt.savefig('entropy_py.png')
plt.show()