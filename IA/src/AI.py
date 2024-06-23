
import time
import random

"""
Rarity based on quantity of resources needed:

#### Sorted by Ratio ####
| Resource  | Ratio   | ID |
|-----------|---------|----|
| Sibur     | 0.01    | 0  |
| Phiras    | 0.0133  | 1  |
| Deraumere | 0.01875 | 2  |
| Mendiane  | 0.02    | 3  |
| Linemate  | 0.0375  | 4  |
| Thystame  | 0.05    | 5  |
##########################

Sorted by ratio:
1. Sibur
2. Phiras

"""

levels = [
    # {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
]

resources_to_get = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

for level in levels:
    for resource, amount in level.items():
        resources_to_get[resource] += amount

inventory = {
    "food": 0,
    "linemate": 0,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
}

class AI:
    def __init__(self, id=0):
        self.level = 1
        self.id = id
        self.inventory = inventory
        self.vision = []
        self.direction = 'Down'
        self.team = ''
        self.x = 0
        self.y = 0
        self.queue = []
        self.start = time.time()
        self.mode = 'Normal'
        self.broadcaster_direction = -1 # default value (no broadcaster)
        self.count_incanter = 0

        self.resources_to_get = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        # resource to get is going to be based on the id of the player (first will need to get the linemate, second the deraumere, etc.)
        if self.id == 0:
            self.resources_to_get['sibur'] = resources_to_get['sibur']
        elif self.id == 1:
            self.resources_to_get['phiras'] = resources_to_get['phiras']
        elif self.id == 2:
            self.resources_to_get['deraumere'] = resources_to_get['deraumere']
        elif self.id == 3:
            self.resources_to_get['mendiane'] = resources_to_get['mendiane']
        elif self.id == 4:
            self.resources_to_get['linemate'] = resources_to_get['linemate']
        elif self.id == 5:
            self.resources_to_get['thystame'] = resources_to_get['thystame']
        
        self.has_all_resources_dict = {"linemate": False, "deraumere": False, "sibur": False, "mendiane": False, "phiras": False, "thystame": False}

    def map_resource(self, id):
        resources = {
            0: 'sibur',
            1: 'phiras',
            2: 'deraumere',
            3: 'mendiane',
            4: 'linemate',
            5: 'thystame'
        }
        return resources.get(id, 'Unknown resource')
    
    def has_all_resources_dict_func(self):
        for resource, value in self.has_all_resources_dict.items():
            if value == False:
                return False
        return True

    def parse_inventory(self, response):
        if self.detect_type_of_response(response) != 'inventory':
            return None
        inventory = {}
        response = response.strip('[]')
        list_of_items = response.split(', ')
        for item in list_of_items:
            parts = item.split()
            if len(parts) == 2:
                key, value = parts
                inventory[key] = int(value)
            else:
                print(f"Unexpected inventory item format: {item}")
        return inventory
    
    def _parse_input_list(self, row_list):
        removed_brackets = row_list.replace('[', '').replace(']', '')
        converted_list = []
        list_of_tiles = removed_brackets.split(',')
        for elt in list_of_tiles:
            converted_list.append(elt.split())
        return converted_list
    
    def _create_list_of_dicts(self, vision):
        list_of_dicts = []
        i = 0
        while len(vision) > 0:
            width = 1 + 2 * i
            list_of_dicts.append(vision[:width])
            vision = vision[width:]
            i += 1
        return list_of_dicts
    
    def _fill_empty_elements(self, list_of_dicts):
        for row in list_of_dicts:
            for i, cell in enumerate(row):
                if cell == []:
                    row[i] = [None]

    def _pad_rows(self, list_of_dicts):
        len_last_row = len(list_of_dicts[-1])
        new_list = []
        for row in list_of_dicts:
            nb_spaces = (len_last_row - len(row)) // 2
            new_row = [[None]] * nb_spaces + row + [[None]] * nb_spaces
            new_list.append(new_row)
        return new_list
    
    def _list_to_dict(self, tile_list):
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
    
    def _convert_elements_to_dicts(self, padded_list):
        for i in range(len(padded_list)):
            for j in range(len(padded_list[i])):
                padded_list[i][j] = self._list_to_dict(padded_list[i][j])
        return padded_list
    
    def parse_vision(self, input_message):
        vision = self._parse_input_list(input_message.strip('[]'))
        list_of_dicts = self._create_list_of_dicts(vision)
        self._fill_empty_elements(list_of_dicts)
        padded_list = self._pad_rows(list_of_dicts)
        final_list = self._convert_elements_to_dicts(padded_list)
        return final_list
    
    def get_type_inventory_look(self, response):
        try:
            inventory_string = response.strip("[] ")
            items = inventory_string.split(", ")
            inventory_dict = {}

            for item in items:
                key, value = item.split(" ")
                inventory_dict[key] = int(value)

            return 'inventory'
        except:
            return 'look'
        
    
    def detect_type_of_response(self, response):
        if response.startswith('ok'):
            return 'ok'
        if response.startswith('ko'):
            return 'ko'
        if response.startswith('['):
            return self.get_type_inventory_look(response)
        if response.startswith('message'):
            return 'broadcast'
        if response.startswith('dead'):
            return 'dead'
        if response.startswith('Elevation underway'):
            return 'elevation'
        if response.startswith('Current level:'):
            return 'level up'
        
        return 'unknown'
    
    def update_state(self, response):
        type_of_response = self.detect_type_of_response(response)
        if type_of_response == 'inventory':
            self.inventory = self.parse_inventory(response)
        if type_of_response == 'look':
            self.vision = self.parse_vision(response)
        if type_of_response == 'level up':
            self.level = int(response.split()[-1])
            print(f"Level up! New level: {self.level}")
    
    def set_direction(self, goal_direction):
        if self.direction == goal_direction:
            return
        
        idx_directions = ['Left', 'Up', 'Right', 'Down']
        idx_goal = idx_directions.index(goal_direction)
        idx_current = idx_directions.index(self.direction)
        diff = idx_goal - idx_current
        if diff == 1 or diff == -3:
            self.queue.append('Left')
        elif diff == 2 or diff == -2:
            self.queue.append('Right')
            self.queue.append('Right')
        elif diff == 3 or diff == -1:
            self.queue.append('Right')
        self.direction = goal_direction

    def move_direction(self, goal_direction):
        self.set_direction(goal_direction)
        self.queue.append('Forward')

    def move_to(self, goal_x, goal_y):
        
        vertical_direction = 'Down' if goal_y > self.y else 'Up'
        horizontal_direction = 'Right' if goal_x > self.x else 'Left'

        while self.y != goal_y:
            self.move_direction(vertical_direction)
            if vertical_direction == 'Down':
                self.y += 1
            else:
                self.y -= 1

        while self.x != goal_x:
            self.move_direction(horizontal_direction)
            if horizontal_direction == 'Right':
                self.x += 1
            else:
                self.x -= 1

    def take_resources(self, resource):
        state = False
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                try:
                    if cell[resource] > 0:
                        self.move_to(j, i)
                        for _ in range(cell[resource]):
                            self.queue.append(f'Take {resource}')
                        state = True
                except:
                    print(f"{resource} doesn't exist")
        return state
    
    def has_all_resources(self):
        for resource, amount in self.inventory.items():
            if resource == 'food':
                continue
            if amount < self.resources_to_get[resource]:
                return False
        return True

    def take_resources_to_get(self):
        state = False

        goal_inventory = self.resources_to_get
        goal_inventory['food'] = 50
        resources_to_collect = {k: v for k, v in goal_inventory.items() if v > self.inventory[k]}

        for resource, amount_needed in resources_to_collect.items():
            amount_to_collect = amount_needed - self.inventory[resource]
            if amount_to_collect <= 0:
                continue

            for i, row in enumerate(self.vision):
                for j, cell in enumerate(row):
                    if cell.get(resource, 0) > 0:
                        self.move_to(j, i)
                        for _ in range(min(amount_to_collect, cell[resource])):
                            self.queue.append(f'Take {resource}')
                            amount_to_collect -= 1
                        if amount_to_collect <= 0:
                            state = True
                            break
                if amount_to_collect <= 0:
                    break
        return state


    def reset_direction(self):
        self.direction = 'Down'

    def linemate_level1(self):
        state = False
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                try:
                    if cell['linemate'] > 0:
                        self.move_to(j, i)
                        self.queue.append('Incantation')
                        state = True
                        return state
                except:
                    print(f"linemate doesn't exist")
        return state

    def drop_resources(self):
        for resource, amount in self.inventory.items():
            if resource == 'food':
                continue
            for _ in range(amount):
                self.queue.append(f'Set {resource}')
        self.inventory = inventory
        return self.queue

    def algorithm(self):
        # Set initial position and direction of the player in the vision grid
        self.y = 0
        self.x = len(self.vision[0]) // 2
        self.reset_direction()

        # Prioritize taking food first
        if self.inventory['food'] < 15 or self.has_all_resources():
            if not self.take_resources('food'):
                self.queue.append(random.choice(['Left', 'Right', 'Forward']))
                self.queue.append('Forward')
                self.queue.append('Forward')
            return self.queue
        
        if self.level == 1:
            self.linemate_level1()
            return self.queue
        
        if not self.take_resources_to_get():
            self.queue.append(random.choice(['Left', 'Right', 'Forward']))
            self.queue.append('Forward')
            self.queue.append('Forward')
        return self.queue
        
    def action_to_broadcaster(self):
        if self.broadcaster_direction == 1 or self.broadcaster_direction == 2 or self.broadcaster_direction == 8:
            return 'Forward'            

        if self.broadcaster_direction == 3 or self.broadcaster_direction == 4 or self.broadcaster_direction == 5:
            return 'Left'

        if self.broadcaster_direction == 6 or self.broadcaster_direction == 7:
            return 'Right'
        
        return None
