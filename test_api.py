import random
import lpcnet


c = []

for i in range(5):
    c.append( [random.random() + random.randint(-4,4) for k in range(55) ] )

print(c)
d = lpcnet.run_for_chunk(c)

print("Output:", d)
