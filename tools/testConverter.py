####################
## Test Converter ##
####################
## A free script to convert a text file into a TestDesk compatible JSON file.

# Imports
import json
import sys
import os

import providers.messer as MSR
import providers.vceplus as VCE

# Variables
result = {
  "name": None,
  "description": None,
  "questions": []
}
commands = [
  {
    "token": "--name"
  },
  {
    "token": "--desc"
  },
  {
    "token": "--in"
  },
  {
    "token": "--out"
  }
]
args = []

quizProvider = 0
quizPath = ""
quizOut = ""

# Functions
def readArgs():
  global commands, args
  for arg in range(len(sys.argv)):
    for cmd in commands:
      if(cmd["token"] == sys.argv[arg]):
        args.append({
          "key": cmd["token"],
          "value": sys.argv[arg+1]
        })
        arg += 1
    
def argExists(key):
  global args
  for arg in args:
    if(arg["key"] == key):
      return True
  return False
def argValue(key):
  global args
  for arg in args:
    if(arg["key"] == key):
      return arg["value"]
  return None

def getMetadata():
  global result, quizProvider, quizPath, quizOut

  # Asking for a test name and description
  if(argExists("--name")):
    result["name"] = argValue("--name")
  else:
    result["name"] = input("Give your test a name.\n[Test Name]: ")
  if(argExists("--desc")):
    result["description"] = argValue("--desc")
  else:
    result["description"] = input("Describe what your test is for.\n[Description]: ")

  # Asking for quiz provider
  print("Select the provider that has given you the PDF file.")
  print("1. VCEplus")
  print("2. Professor Messer")
  quizProvider = int(input("[Provider]: "))

  # Asking for quiz info
  if(argExists("--in")):
    quizPath = argValue("--in")
  else:
    quizPath = input("Drag and Drop your text file into this window\n(Use https://pdftotext.com/ to convert your PDF file into a text file.)\n[In Location]: ")
  if(argExists("--out")):
    quizOut = argValue("--out")
  else:
    quizOut = input("Write a path to where you want to save your JSON file (ex: data/exams/test.json)\nYour Working Directory: " + os.getcwd() + "\n[Out Location]: ")
def readFile():
  global quizPath, quizProvider, result
  
  # Opening quiz
  quizFile = open(quizPath, 'r')

  # Did the user type it in wrong?
  if(quizFile == None):
    print("ERROR: Invalid path for Quiz!")
    exit()

  # Based on provider, LOAD
  match(quizProvider):
    case 1:
      questions = VCE.ParseVCE(quizFile.readlines())
    case 2:
      questions = MSR.ParseMesser(quizFile.readlines())
  
  # Result
  result["questions"] = questions

def writeFile():
  global quizOut, result

  quizFile = open(quizOut, 'w')
  quizFile.write(json.dumps(result))
  quizFile.close()

def main():
  readArgs()
  getMetadata()
  readFile()
  writeFile()

# Entry Point
main()