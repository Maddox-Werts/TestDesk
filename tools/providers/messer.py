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

def ParseMesser(lines):
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
                if("Practice Exam A - Answers" in line
                or "Practice Exam B - Answers" in line
                or "Practice Exam C - Answers" in line):
                    state = 1
            case 1: # Writing into prompt
                if("*" in line):
                    if("PICK TWO" in line):
                      state = 0
                      tempQuestion = {
                            "type": 0,
                            "prompt": "",
                            "responses": [],
                            "correct": 0
                        }
                    state = 2
                else:
                    for l in line:
                      if(l == '\n'):
                        tempQuestion["prompt"] += " "
                      else:
                        tempQuestion["prompt"] += l
            case 2: # Awaiting for answers
                if(line == "" or line == " " or line == "\n" or line == None):
                    state = 3
            case 3: # Adding responses
                if(line == "" or line == " " or line == "\n" or line == None):
                    state = 4
                else:
                    if(len(line.split(".")) <= 1):
                        print("SKIPED QUESTION: " + tempQuestion["prompt"])
                        tempQuestion = {
                            "type": 0,
                            "prompt": "",
                            "responses": [],
                            "correct": 0
                        }
                        state = 0
                    else:
                        tempQuestion["responses"].append(line.split(".")[1])
            case 4: # Awaiting for Correct Answer
                if("The Answer" in line):
                    tempQuestion["correct"] = Letter2Number(line.split(":")[1].split(".")[0])
                    result.append(tempQuestion)
                    tempQuestion = {
                        "type": 0,
                        "prompt": "",
                        "responses": [],
                        "correct": 0
                    }
                    state = 0
    
    return result