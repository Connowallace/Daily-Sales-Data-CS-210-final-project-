import re
import string

# Static dictionary variable used by multiple functions
# Note: I originally thought I could just fill this dictionary once and use that dictionary
# for the functions. That worked in PyCharm, but not in the C++ calls BECAUSE THE SCRIPT TERMINATES 
# EACH TIME. My fix was to add the fill the dictionary call to each function.
the_dictionary = {}


# Print the menu
def printMenu():
    # New line for whitespace
    print()
    print("1: Display a list of each item sold, and quantity of that item sold")
    print("2: Number of times a specific item was purchased")
    print("3: Display histogram of all items sold")
    print("4: Exit")
    print("Enter your selection as a number 1, 2, 3 or 4.")


def fill_dictionary_with_data():
    # Open the file with input validation
    try:
        file = open("sold_items_data.txt")
    except FileNotFoundError:
        print("Wrong file or file path in fill_dictionary_with_data")
        # End the function if file is not found
        return

    # Iterate through each line in the file
    for item in file:
        # Remove whitespace
        item = item.strip()
        # If item is already in the dictionary up its count by one
        if item in the_dictionary.keys():
            the_dictionary[item] = the_dictionary.get(item) + 1
        # Else add the item to the dictionary with a count of one
        else:
            the_dictionary[item] = 1

    # Close the file
    file.close()


def print_the_dictionary():
    fill_dictionary_with_data()
    for keys, values in the_dictionary.items():
        print("{}: {}".format(keys, values))


def write_the_dictionary():
    fill_dictionary_with_data()

    # Open/create file
    output_file = open('frequency.dat', 'w')
    # Write each item and quantity to a line
    for keys, values in the_dictionary.items():
        output_file.write("{} {}\n".format(keys, values))

    # Close the file
    output_file.close()


def num_times_sold(item_name):
    fill_dictionary_with_data()

    # If the key is not in the dictionary, print error message and return -1
    if the_dictionary.get(item_name, -1) == -1:
        print('Item not found!')

    return the_dictionary.get(item_name, -1)