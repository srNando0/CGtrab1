import os
import json



class Compile:
	def __init__(self):
		doExit = False
		
		while not doExit:
			string = input("======> ")
			
			if string == 'compile' or string == 'a':
				self.compile()
			elif string == 'link' or string == 'l':
				self.link()
			elif string == 'run' or string == 'r':
				self.run()
			elif string == 'clear' or string == 'c':
				os.system('cls')
			elif string == 'exit' or string == 'e':
				break
			elif string == 'main' or string == 'm':
				os.system('cls')
				self.compileObject('main')
				self.link()
				self.run()
			else:
				self.compileObject(string)
	
	
	
	def loadData(self):
		with open('compileData.json') as f:
			self.data = json.load(f)
	
	
	
	def createDirectory(self, path):
		if not os.path.exists(path):
			os.mkdir(path)
		
	
	
	
	def compileObject(self, file):
		self.loadData()
		
		strVersion = self.data['version']
		strLibraries = ' '.join(self.data['libraries'])
		strCppfile = f'{self.data['source folder']}/{file}.cpp'
		strObjectFile = f'{self.data['objects folder']}/{file}.o'
		
		strDirname, _ = os.path.split(strObjectFile)
		self.createDirectory(strDirname)
		
		string = f'clang++ {strVersion} {strLibraries} {strCppfile} -c -o {strObjectFile}'
		print(string)
		os.system(string)
	
	
	
	def compile(self):
		self.loadData()
		
		strVersion = self.data['version']
		strLibraries = ' '.join(self.data['libraries'])
		strSourceFolder = self.data['source folder']
		strObjectsFolder = self.data['objects folder']
		
		for file in self.data['files']:
			strDirname, _ = os.path.split(file)
			self.createDirectory(f'{strObjectsFolder}/{strDirname}')
			
			string = f'clang++ {strVersion} {strLibraries} {strSourceFolder}/{file}.cpp -c -o {strObjectsFolder}/{file}.o'
			print(string)
			os.system(string)
	
	
	
	def link(self):
		self.loadData()
		strObjectsFolder = self.data['objects folder']
		strObjects = f'{strObjectsFolder}/' + f'.o {strObjectsFolder}/'.join(self.data['files']) + '.o'
		strOutput = self.data['output']
		
		string = f'clang++ {strObjects} -o {strOutput}'
		print(string)
		os.system(string)
	
	
	
	def run(self):
		strDirname, strBasename = os.path.split(self.data['output'])
		string = f'start /min cmd /k "cd {strDirname}&{strBasename}"'
		print(string)
		os.system(string)



if __name__ == '__main__':
	compile = Compile()