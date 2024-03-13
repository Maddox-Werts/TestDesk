#     ##################
#     #   PDF -> JSON  #
#     #  for TestDesk  #
#     ##################

#       This tool is to help automatically sort PDF content into a TestDesk compatible JSON file
#       to study from. This tool is EXTREMELY EXPERIMENTAL!

# Imports

# Variables
result = {
  "name": None,
  "description": None,
  "questions": []
}
pdfText = ""

# Functions
def createHeaderInfo():
  global result

  print("Header Information")
  print("------------------")
  result["name"] = input("Give your test a name\n> ")
  result["description"] = input("Briefly give your test a description\n> ")

def readingLines():
  global pdfText
  pass

def main():
  createHeaderInfo()
  readingLines()

# Entry Point
main()