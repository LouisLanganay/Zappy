def convert_to_a_list_of_dicts(row_list):
    vision = parse_input_list(row_list)
    list_of_dicts = create_list_of_dicts(vision)
    fill_empty_elements(list_of_dicts)
    padded_list = pad_rows(list_of_dicts)
    final_list = convert_elements_to_dicts(padded_list)
    return final_list

def parse_input_list(row_list):
    removed_brackets = row_list.replace('[', '').replace(']', '')
    converted_list = []
    list_of_tiles = removed_brackets.split(',')
    for elt in list_of_tiles:
        converted_list.append(elt.split())
    return converted_list

def create_list_of_dicts(vision):
    list_of_dicts = []
    i = 0
    while len(vision) > 0:
        width = 1 + 2 * i
        list_of_dicts.append(vision[:width])
        vision = vision[width:]
        i += 1
    return list_of_dicts

def fill_empty_elements(list_of_dicts):
    for i in range(len(list_of_dicts)):
        for j in range(len(list_of_dicts[i])):
            if list_of_dicts[i][j] == []:
                list_of_dicts[i][j] = [None]

def pad_rows(list_of_dicts):
    len_last_row = len(list_of_dicts[-1])
    new_list = []
    for row in list_of_dicts:
        new_row = []
        nb_spaces = (len_last_row - len(row)) // 2
        new_row.extend([[None]] * nb_spaces)
        new_row.extend(row)
        new_row.extend([[None]] * nb_spaces)
        new_list.append(new_row)
    return new_list

def convert_elements_to_dicts(padded_list):
    for i in range(len(padded_list)):
        for j in range(len(padded_list[i])):
            padded_list[i][j] = list_to_dict(padded_list[i][j])
    return padded_list

def list_to_dict(tile_list):
    tile = {
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
    for elt in tile_list:
        if elt in tile:
            tile[elt] += 1
    return tile


row_list = "[ player,, food food, deraumere ]"

row_list = "[player,,,thystame,,food,,,,,thystame,,,,,]"

list_of_dicts = convert_to_a_list_of_dicts(row_list)
print(list_of_dicts)