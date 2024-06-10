# row_list = "[ player,, food food, deraumere ]"
# goal_list = [['player'], [], ['food', 'food'], ['deraumere']]

# def test_parse_vision(list1, list2):
#     if list1 == list2:
#         print("Test passed")
#     else:
#         print("Test failed")

# def parse_input_list(row_list):
#     # removed_brackets = row_list[1:-1]
#     removed_brackets = row_list.replace('[', '').replace(']', '')
#     converted_list = []
#     list_of_tiles = removed_brackets.split(',')
#     for elt in list_of_tiles:
#         converted_list.append(elt.split())
#     return converted_list

# converted_list = parse_input_list(row_list)
# test_parse_vision(converted_list, goal_list)





# row_input = "[ food 8, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0 ]"

# def parse_inventory(row_input):
#     inventory = {}
#     row_input = row_input.strip('[]')

#     list_of_items = row_input.split(', ')
#     for item in list_of_items:
#         key, value = item.split()
#         inventory[key] = int(value)
#     return inventory

# print(parse_inventory(row_input))


# Vision parsing
# Its going to be a 

tile_data = {
    "player": 0,
    "food": 0,
    "linemate": 0,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0,
    "egg": 0
}

level = 1

row_list = "[ player,, food food, deraumere ]"

def parse_input_list(row_list):
    # removed_brackets = row_list[1:-1]
    removed_brackets = row_list.replace('[', '').replace(']', '')
    converted_list = []
    list_of_tiles = removed_brackets.split(',')
    for elt in list_of_tiles:
        converted_list.append(elt.split())
    return converted_list

# print(parse_input_list(row_list))

def convert_to_a_list_of_dicts(row_list):
    list_of_dicts = []
    vision = parse_input_list(row_list)
    len_vision = len(vision)
    level = 1
    max_width = 1 + 2 * level

    for i in range(level + 1):
        width = 1 + 2 * i
        list_of_dicts.append(vision[:width])
        vision = vision[width:]
    
    '''
    list_of_dicts =
    [
    [['player']],
    [[], ['food', 'food'], ['deraumere']]
    ]

    i want to convert it to
    [[None], ['player'], [None]],
    [[None], ['food', 'food'], ['deraumere']]
    '''
    for i in range(len(list_of_dicts)):
        for j in range(len(list_of_dicts[i])):
            if list_of_dicts[i][j] == []:
                list_of_dicts[i][j] = [None]

    len_last_row = len(list_of_dicts[-1])
    # print(len_last_row)
    new_list = []
    for i in range(len(list_of_dicts)):
        new_row = []
        elt = list_of_dicts[i]
        # we are going to add certain number of list of none at the beginning of the list and at the end of the list
        nb_spaces = (len_last_row - len(elt)) // 2
        # new_list.append([None] * nb_spaces + elt + [None] * nb_spaces)
        # add some list which contains only None at the beginning of the list and at the end of the list
        for j in range(nb_spaces):
            new_row.append([None])
        # new_row.append(elt)
        for element in elt:
            new_row.append(element)
        for j in range(nb_spaces):
            new_row.append([None])
        new_list.append(new_row)


    '''
    [
        [None, ['player'], None], [[None], ['food', 'food'], ['deraumere']]
    ]
    '''
    # print(new_list)
    return new_list

    # print(max_width)
    # for i 
    # print(list_of_dicts)
    # print(len(list_of_dicts))
    # we are going to convert [['player'], [], ['food', 'food'], ['deraumere']] to
    # to 
    # [['player']],
    # [[None], ['food', 'food'], ['deraumere']]

    # print(vision)

    
# row_list = "[player,,,thystame,,food,,,,,thystame,,,,,,]"
row_list = "[ player,, food food, deraumere ]"

print(convert_to_a_list_of_dicts(row_list))
# the first step is to convert it into a list of items
# the second step is to convert it into a dictionary


# def parse_tile(row_list):
#     tile = tile_data
#     row_list = row_list.replace('[', '').replace(']', '')
#     list_of_items = row_list.split(', ')
#     for item in list_of_items:
#         if item in tile:
#             tile[item] += 1
#     return tile

# print(parse_tile(row_list))
# here is an example of a single tile



# def parse_tile(tile_list):

# inventory = {
#     "food": 0,
#     "linemate": 0,
#     "deraumere": 0,
#     "sibur": 0,
#     "mendiane": 0,
#     "phiras": 0,
#     "thystame": 0,
#     "player": 0,
#     "egg": 0
# }

