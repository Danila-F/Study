import math

c = 2771
d = 2147
n = 3337
m = 2
#y = math.pow(m, d) % n

x = 1
for i in range(0, d):
    x = (x * c) % n

print(x)
#x = (math.pow(c, d)) % n
