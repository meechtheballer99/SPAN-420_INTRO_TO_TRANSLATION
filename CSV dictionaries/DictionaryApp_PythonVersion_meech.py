import sys  # import the sys module

# set a default filename and max results
filename = "es-en.csv"
max_results = 0

# welcome message
print("Welcome to the line-by-line search program [python version] (built to search span-english dictionary - for SPAN-420 UM-DEARBORN)")
print("By Demetrius Johnson (Meech)")

# prompt the user for a filename and max results
filename = input("Input a dictionary - or any txt or csv - filename to do line-by-line word search\n"
                 "(make sure the file is in the same directory as where you launched this program, or specify full path including filename):\nEnter file name: ")
max_results = int(input("Enter the MAX number of results you want displayed (lines in the file that contain your search word): "))

try:
    # try to open the file
    with open(filename, 'r') as dictionary:
        word = ""  # initialize the word variable
        line = ""  # initialize the line variable
        count = 0  # initialize the count variable
        line_count = 0  # initialize the line count variable
        while True:
            word = input("Input a word to search for (q to quit): ")  # prompt the user for a word to search for
            if word == "q":  # if the user enters "q", exit the loop
                break
            for line in dictionary:  # loop through each line in the file
                line_count += 1  # increment the line count
                if word in line:  # if the word is in the line
                    count += 1  # increment the count
                    # print the search result, including the count and line number
                    print(f"search_result_{count} [line#{line_count}]: {line}",end='')
                    if count == max_results:  # if the max results has been reached, exit the loop
                        break
            if count == 0:  # if no results were found, print an error message
                print(f"************\"{word}\" NOT FOUND IN \"{filename}\" FILE**********\n***IF ERROR SUSPECTED, RELAUNCH PROGRAM AND CHECK INPUT********\n")
            else:  # otherwise, print the end of search results message
                print(f"\n-------------------END OF SEARCH RESULTS FOR \"{word}\" IN \"{filename}\" (MAX SET TO {max_results})----------------\n\n")
            dictionary.seek(0)  # reset the file pointer to the beginning of the file
            count = 0  # reset the count variable
            line_count = 0  # reset the line count variable
except FileNotFoundError:  # if the file is not found, print an error message and exit
    print(f"\"{filename}\" dictionary file not found or opened, program will exit")
    sys.exit(1)

# print the exiting message
print("program exiting...")
