#!/usr/bin/python3
import unittest
import subprocess

class EncodeTest(unittest.TestCase):
	def test1(self):
		print()
		with open("./tests/outputEncode1.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--encode", "--file", "tests/testEncode1.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test2(self):
		print()
		with open("./tests/outputEncode2.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--encode", "--file", "tests/testEncode2.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test3(self):
		print()
		with open("./tests/outputEncode3.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--encode", "--file", "tests/testEncode3.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test4(self):
		print()
		with open("./tests/outputEncode4.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--encode=8", "--file", "tests/testEncode4.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test5(self):
		print()
		with open("./tests/outputEncode5.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--encode=16", "--file", "tests/testEncode5.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

class DecodeTest(unittest.TestCase):
	def test1(self):
		print()
		with open("./tests/outputDecode1.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testDecode1.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test2(self):
		print()
		with open("./tests/outputDecode2.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testDecode2.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test3(self):
		print()
		with open("./tests/outputDecode3.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testDecode3.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test4(self):
		print()
		with open("./tests/outputDecode4.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testDecode4.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

	def test5(self):
		print()
		with open("./tests/outputDecode5.txt", 'r') as file:
			programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testDecode5.txt"], universal_newlines = True)[:-1]
			correctResult = file.read()
			print("Program output:", programResult)
			print("Correct output:", correctResult)
			self.assertEqual(programResult, correctResult)
		print()

class ErrorTest(unittest.TestCase):
	def test1(self):
		print()
		programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testError1.txt"], stderr=subprocess.STDOUT, universal_newlines = True)[:-1]
		print("Program output:", programResult[0 : 5])
		print("Correct output: Error")
		print()
		self.assertIn("Error", programResult)
		print()

	def test2(self):
		print()
		programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testError2.txt"], stderr=subprocess.STDOUT, universal_newlines = True)[:-1]
		print("Program output:", programResult[0 : 5])
		print("Correct output: Error")
		print()
		self.assertIn("Error", programResult)
		print()

	def test3(self):
		print()
		programResult = subprocess.check_output(["./cw", "--decode", "--file", "tests/testError3.txt"], stderr=subprocess.STDOUT, universal_newlines = True)[:-1]
		print("Program output:", programResult[0 : 5])
		print("Correct output: Error")
		print()
		self.assertIn("Error", programResult)
		print()

if __name__ == '__main__':
	unittest.main()
