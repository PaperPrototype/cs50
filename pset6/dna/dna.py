from sys import argv
import csv
import collections

def main():

    if not len(argv) == 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return


    ''' LOAD DNA DATABASE AND SEQUENCE INTO MEMORY '''
    print("### LOAD DNA DATABASE AND SEQUENCE INTO MEMORY\n")

    # dna database
    database = list()       # database of people
    sequence_string = str() # the current subjects dna sequence
    subject = str()          # the current subjects data


    # read and save dna database
    csv_file = open(argv[1], mode='r')
    for row in csv.reader(csv_file):
        # add to database
        database.append(row)
    csv_file.close()

    # reading sequence txt into a string
    sequence_file = open(argv[2], 'r')
    sequence_string = sequence_file.read()
    sequence_file.close()

    ''' for each STR compute the longest run of reapeats (in that subjects sequence)'''
    print("### for each STR compute the longest run of reapeats (in that subjects sequence)\n")

    subject = database[0][1:len(database[0])]

    print(subject)

    # for each dna STR
    for i_STR in range(1, len(database[0])):

        # cur STR pattern to look for
        cur_STR = database[0][i_STR]

        # print out cur STR
        print(f"longest repeat {cur_STR}: ", end="")

        longest_repeat = 0

        # iterate over entire dna sequence
        for i in range(len(sequence_string)):

            cur_repeats = 0

            cur_i = i
            # repeat while cur STR matches
            while sequence_string[cur_i:cur_i+len(cur_STR)] == cur_STR:

                # cur_repeats ++
                # print("found", end="")
                cur_repeats += 1

                # go to next STR
                cur_i += len(cur_STR)

            # if current repeats is larger than longest repeat
            if cur_repeats > longest_repeat:
                # longest_repeat = cur_repeat
                longest_repeat = cur_repeats

        print(longest_repeat)
        subject[i_STR - 1] = longest_repeat

    print(f"Subjects dna sequence: {subject}", end="\n\n")


    ''' search through database for match with sequence '''
    print("### search through database for match with sequence\n")

    # convert subject dna list to str list
    subject = [str(i) for i in subject]

    # go through each person in database
    for i in range(1, len(database)):

        # set cur person to current index of database
        cur_person = database[i][1:len(database[i])]

        # if subject dna sequence matches person in database
        if collections.Counter(subject) == collections.Counter(cur_person):

            # print match found
            print(f"Found match {cur_person} {database[i][0]}")
            return

        print(cur_person)

    else: # if loop ends
        print("\nNo match")



if __name__ == "__main__":
    main()