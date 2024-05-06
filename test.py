import os



def pathSplit(path):
	if path == '':
		return ()
	head, tail = os.path.split(path)
	return pathSplit(head) + (tail,)



path = 'src/core/renderer.cpp'
print(pathSplit(path))
print(os.path.split(path))
print((1,) + (2,) + (3,))
os.mkdir('cuuu')