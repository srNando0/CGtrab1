import os
import json



class Compile:
	def __init__(self):
		doExit = False
		
		while not doExit:
			actionList = list(input("================\na - compile all\nc - clear terminal\ne - exit from terminal\nf - fast compile\nr - run the build\n")[::-1])
			
			while 0 < len(actionList):
				action = actionList.pop()
				
				if action == "a":
					self.compile()
				elif action == "c":
					os.system("cls")
				elif action == "e":
					doExit = True
					break
				elif action == "f":
					self.compileFast()
				elif action == "r":
					self.run()
				else:
					print(f'"{action}" is not an action!')
	
	
	
	def loadData(self):
		with open("compileData.json") as f:
			self.data = json.load(f)
	
	
	
	def compile(self):
		self.loadData()
		strVersion = self.data["version"]
		strLibraries = " ".join(self.data["libraries"])
		strInputs = " ".join(self.data["inputs"])
		string = f'clang++ {strVersion} {strLibraries} {strInputs} -o {self.data["output"]}'
		print(string)
		os.system(string)
	
	
	
	def compileFast(self):
		self.loadData()
		strVersion = self.data["version"]
		strLibraries = " ".join(self.data["libraries"])
		strInputs = " ".join(self.data["fast inputs"])
		string = f'clang++ {strVersion} {strLibraries} {strInputs} -o {self.data["output"]}'
		print(string)
		os.system(string)
	
	
	
	def run(self):
		strDirname, strBasename = os.path.split(self.data["output"])
		string = f'start cmd /k "cd {strDirname}&{strBasename}"'
		print(string)
		os.system(string)



if __name__ == "__main__":
	compile = Compile()