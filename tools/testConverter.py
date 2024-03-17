####################
## Test Converter ##
####################
## A free script to convert a text file into a TestDesk compatible JSON file.

# Imports
import sys
import os

import providers.vceplus as VCE

# Variables
result = {
  "name": None,
  "description": None,
  "questions": []
}

quizProvider = 0
quizPath = ""
quizOut = ""

# Functions
def getMetadata():
  global result, quizProvider, quizPath, quizOut

  # Asking for a test name and description
  result["name"] = input("Give your test a name.\n[Test Name]: ")
  result["description"] = input("Describe what your test is for.\n[Description]: ")

  # Asking for quiz provider
  print("Select the provider that has given you the PDF file.")
  print("1. VCEplus")
  quizProvider = int(input("[Provider]: "))

  # Asking for quiz info
  quizPath = input("Drag and Drop your text file into this window\n(Use https://pdftotext.com/ to convert your PDF file into a text file.)\n[In Location]: ")
  quizOut = input("Write a path to where you want to save your JSON file (ex: data/exams/test.json)\nYour Working Directory: " + os.getcwd() + "\n[Out Location]: ")
def readFile():
  global quizPath
  
  # Opening quiz
  quizFile = open(quizPath, 'r')

  # Did the user type it in wrong?
  if(quizFile == None):
    print("ERROR: Invalid path for Quiz!")
    exit()

  # Based on provider, LOAD
  questions = VCE.ParseVCE(quizFile.readlines())

def main():
  getMetadata()
  readFile()

# Entry Point
main()