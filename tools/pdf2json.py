# Imports
from tika import parser
import json
import sys

## FUNCTIONS ##
def LetterToInt(line):
  match(line):
    case 'A':
      return 0
    case 'B':
      return 1
    case 'C':
      return 2
    case 'D':
      return 3
    case 'E':
      return 4
    case 'F':
      return 5
    case 'G':
      return 6
    case 'H':
      return 7
    case 'I':
      return 8
    case 'J':
      return 9
    case 'K':
      return 10
    case 'L':
      return 11
    case 'M':
      return 12
    case 'N':
      return 13
    case 'O':
      return 14
    case 'P':
      return 15
    case 'Q':
      return 16

  return
def parseQuestions(lines):
  # Result
  result = []
  temp = {
    "type": 0,
    "prompt": "",
    "responses": [],
    "correct": 0
  }
  state = 0

  # Going through lines
  for i in range(len(lines)):
    # Line
    line = lines[i]

    # Quick Checks
    isEmpty = line == "" or line == " " or line == "\n"

    # Switching based on States
    match(state):
      case 0:
        temp = {
          "type": 0,
          "prompt": "",
          "responses": [],
          "correct": 0
        }

        if("QUESTION" in line):
          state = 1
      case 1:
        temp["prompt"] += line

        if(isEmpty):
          state = 2
      case 2:
        if("." in line):
          if(len(line.split('.')) > 1):
            qtext = line.split('.')[1]
            temp["responses"].append(qtext)
        
        if("Correct Answer" in line):
          if(len(line.split('.')) > 1):
            qanswer = line.split(": ")[1]

            if(len(qanswer) == 1):
              temp["correct"] = LetterToInt(qanswer)
              state = 3
            else:
              state = 0

      case 3:
        if("Section" in line):
          result.append(temp)
          state = 0
  
  # Return result
  return result

## ENTRY POINT ##

# Did we specify the right amount of arguments?
if(len(sys.argv) < 1):
  print("Usage: pdf2json.py [PDF FILE]")
  exit()

# Storing path
pdfPath = sys.argv[1]

# Getting file and parsing it
raw = parser.from_file(pdfPath)

# Splitting up lines
lines = raw['content'].split('\n')

result = parseQuestions(lines)

print ("SUCCESS")

savePath = input("Path to save: ")

newFile = open(savePath, 'w')
newFile.write(json.dumps(result))
newFile.close()