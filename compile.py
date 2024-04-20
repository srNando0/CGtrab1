import os
import json



class Compile:
	def __init__(self):
		doExit = False
		
		while not doExit:
			actionList = list(input("================\nb - compile a build\nc - clear terminal\ne - exit from terminal\nr - run the build\n")[::-1])
			
			while 0 < len(actionList):
				action = actionList.pop()
				
				if action == "b":
					self.compile()
				elif action == "c":
					os.system("cls")
				elif action == "r":
					self.run()
				elif action == "e":
					doExit = True
					break
				else:
					print(f'"{action}" is not an action!')
	
	
	
	def loadData(self):
		with open("compileData.json") as f:
			self.data = json.load(f)
	
	
	
	def compile(self):
		self.loadData()
		strLibraries = " ".join(self.data["libraries"])
		strInputs = " ".join(self.data["inputs"])
		string = f'clang++ {strLibraries} {strInputs} -o {self.data["output"]}'
		print(string)
		os.system(string)
	
	
	
	def run(self):
		strDirname, strBasename = os.path.split(self.data["output"])
		string = f'start cmd /k "cd {strDirname}&{strBasename}"'
		print(string)
		os.system(string)



if __name__ == "__main__":
	compile = Compile()