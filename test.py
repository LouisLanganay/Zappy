
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
    removed_brackets = row_list.replace('[', '').replace(']', '')
    converted_list = []
    list_of_tiles = removed_brackets.split(',')
    for elt in list_of_tiles:
        converted_list.append(elt.split())
    return converted_list

def convert_to_a_list_of_dicts(row_list):
    list_of_dicts = []
    vision = parse_input_list(row_list)
    print('---')
    print(vision)
    print('---')
    len_vision = len(vision)
    level = 1
    

    for i in range(level + 1):
        width = 1 + 2 * i
        list_of_dicts.append(vision[:width])
        vision = vision[width:]
    

    for i in range(len(list_of_dicts)):
        for j in range(len(list_of_dicts[i])):
            if list_of_dicts[i][j] == []:
                list_of_dicts[i][j] = [None]

    len_last_row = len(list_of_dicts[-1])
    new_list = []
    for i in range(len(list_of_dicts)):
        new_row = []
        nb_spaces = (len_last_row - len(list_of_dicts[i])) // 2
        for j in range(nb_spaces):
            new_row.append([None])
        for element in list_of_dicts[i]:
            new_row.append(element)
        for j in range(nb_spaces):
            new_row.append([None])
        new_list.append(new_row)
    return new_list
row_list = "[ player,, food food, deraumere ]"
# row_list = "[player,,,thystame,,food,,,,,thystame,,,,,,]"

print(convert_to_a_list_of_dicts(row_list))

