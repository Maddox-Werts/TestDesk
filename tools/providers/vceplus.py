def Letter2Number(letter):
  if("A" in letter):
    return 0
  if("B" in letter):
    return 1
  if("C" in letter):
    return 2
  if("D" in letter):
    return 3
  if("E" in letter):
    return 4
  if("F" in letter):
    return 5
  if("G" in letter):
    return 6
  if("H" in letter):
    return 7
  if("I" in letter):
    return 8
  if("J" in letter):
    return 9
  if("K" in letter):
    return 10

def ParseVCE(lines):
  # Result object
  result = []

  # Pre-Stuff
  tempQuestion = {
    "type": 0,
    "prompt": "",
    "responses": [],
    "correct": 0
  }
  state = 0

  # Going through lines
  for line in lines:
    match(state):
      case 0: # Awaiting question
        if("QUESTION" in line):
          state = 1
      case 1: # Writing to prompt
        if("A." in line):
          state = 2
        else:
          tempQuestion["prompt"] += line
      case 2: # Awaiting for answers
        if(line == "" or line == " " or line == "\n" or line == None):
          state = 3
      case 3: #Adding responses
        if(line == "" or line == " " or line == "\n" or line == None):
          state = 4
        else:
          tempQuestion["responses"].append(line)
      case 4: # Awaiting for correct answer
        if("Correct" in line):
          print(line)
          tempQuestion["correct"] = Letter2Number(line.split(": ")[1])
        elif("Section: " in line):
          result.append(tempQuestion)
          tempQuestion = {
            "type": 0,
            "prompt": "",
            "responses": [],
            "correct": 0
          }
          state = 0

  # Return result
  return result