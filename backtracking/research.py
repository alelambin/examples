import matplotlib.pyplot as pyplot
import subprocess


def main():
	simple = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
	res = []
	for num in simple:
		programResult = int(subprocess.check_output(['./program', '-c'], input=str(num), universal_newlines = True))
		res.append(programResult)
		#print('{} - {}'.format(num, programResult))
	pyplot.xlabel('The operations number')
	pyplot.ylabel('The table size')
	pyplot.grid(True)
	pyplot.plot(simple, res)
	#pyplot.show()
	pyplot.savefig('plot.png')


if __name__ == '__main__':
	main()
