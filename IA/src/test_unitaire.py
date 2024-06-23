import unittest
from Main import ParseArgs
from Client import AI
from Client import Client

class TestParseMethods(unittest.TestCase):
    def setUp(self):
        self.obj = ParseArgs()

    def test_check_type_valid(self):
        self.obj.port = 8080
        self.obj.name = 'validname'
        self.obj.host = 'localhost'
        self.assertIsNone(self.obj.check_type())  # Expects None if everything is valid

    def test_check_type_invalid_port(self):
        self.obj.port = 'invalid'
        self.assertEqual(self.obj.check_type(), 84)

    def test_check_type_port_minus_one(self):
        self.obj.port = '-1'
        self.obj.name = 'validname'
        self.assertEqual(self.obj.check_type(), 84)

    def test_check_type_empty_name(self):
        self.obj.port = 8080
        self.obj.name = ''
        self.assertEqual(self.obj.check_type(), 84)

    def test_check_host_invalid(self):
        self.assertEqual(self.obj.check_host(), 84)

    def test_check_port_out_of_range_low(self):
        self.obj.port = -1
        self.assertEqual(self.obj.check_port(), 84)

    def test_check_port_out_of_range_high(self):
        self.obj.port = 70000
        self.assertEqual(self.obj.check_port(), 84)

    def test_check_name_too_long(self):
        self.obj.name = 'a' * 33  # 33 characters long
        self.assertEqual(self.obj.check_name(), 84)



    def test_parse_valid_arguments(self):
        args = ['-p', 8080, '-n', 'validname', '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, ('localhost', 8080, 'validname'))

    def test_parse_missing_arguments(self):
        args = ['-p', 8080, '-n', 'validname']
        result = self.obj.parse(args)
        self.assertEqual(result, ('localhost', 8080, 'validname'))

    def test_parse_invalid_argument(self):
        args = ['-x', 8080]
        result = self.obj.parse(args)
        self.assertEqual(result, 84)


    def test_parse_invalid_port_type(self):
        args = ['-p', 'invalid', '-n', 'validname', '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_port_out_of_range(self):
        args = ['-p', 70000, '-n', 'validname', '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_name_too_long(self):
        long_name = 'a' * 33
        args = ['-p', 8080, '-n', long_name, '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_invalid_host(self):
        args = ['-p', 8080, '-n', 'validname', '-h', 'invalid_host']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)











# TEST Client.py


class TestAI(unittest.TestCase):
    def setUp(self):
        self.ai = AI()

    def test_parse_inventory(self):
        response = "[ food 10, linemate 1, deraumere 2, sibur 0, mendiane 0, phiras 1, thystame 0 ]"
        expected_inventory = {
            "food": 10,
            "linemate": 1,
            "deraumere": 2,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 1,
            "thystame": 0
        }
        parsed_inventory = self.ai.parse_inventory(response)
        self.assertEqual(parsed_inventory, expected_inventory)

    def test_parse_inventory_invalid_format(self):
        response = "[ food 10, linemate 1, deraumere two, sibur 0 ]"
        parsed_inventory = self.ai.parse_inventory(response)
        self.assertIsNone(parsed_inventory)

    def test_parse_vision(self):
        input_message = "[ food player, sibur, deraumere linemate, mendiane phiras ]"
        expected_output = [
            [{"player": 1, "food": 1, "linemate": 0, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0, "egg": 0}],
            [{"player": 0, "food": 0, "linemate": 0, "deraumere": 1, "sibur": 0, "mendiane": 1, "phiras": 1, "thystame": 0, "egg": 0}]
        ]
        parsed_vision = self.ai.parse_vision(input_message)
        self.assertEqual(parsed_vision, expected_output)

    def test_detect_type_of_response(self):
        self.assertEqual(self.ai.detect_type_of_response('ok'), 'ok')
        self.assertEqual(self.ai.detect_type_of_response('ko'), 'ko')
        self.assertEqual(self.ai.detect_type_of_response('[ food 10, linemate 1 ]'), 'inventory')
        self.assertEqual(self.ai.detect_type_of_response('message 1, Hello'), 'broadcast')
        self.assertEqual(self.ai.detect_type_of_response('dead'), 'dead')
        self.assertEqual(self.ai.detect_type_of_response('Elevation underway'), 'elevation')
        self.assertEqual(self.ai.detect_type_of_response('Current level: 2'), 'level up')
        self.assertEqual(self.ai.detect_type_of_response('random text'), 'unknown')

    def test_set_direction(self):
        self.ai.direction = 'Down'
        self.ai.set_direction('Up')
        self.assertEqual(self.ai.direction, 'Up')
        self.assertEqual(self.ai.queue, ['Right', 'Right'])

    def test_move_to(self):
        self.ai.x = 0
        self.ai.y = 0
        self.ai.move_to(2, 2)
        self.assertEqual(self.ai.x, 2)
        self.assertEqual(self.ai.y, 2)
        self.assertEqual(self.ai.queue, ['Down', 'Forward', 'Down', 'Forward', 'Right', 'Forward', 'Right', 'Forward'])

    def test_take_resources(self):
        self.ai.vision = [
            [{"player": 0, "food": 1, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0, "egg": 0}],
            [{"player": 0, "food": 0, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0, "egg": 0}]
        ]
        state = self.ai.take_resources('linemate')
        self.assertTrue(state)
        self.assertEqual(self.ai.queue, ['Forward', 'Take linemate'])


    def test_drop_resources_empty_inventory(self):
        self.ai.inventory = {}
        result = self.ai.drop_resources()
        self.assertEqual(result, [])

    def test_drop_resources_with_resource(self):
        self.ai.inventory = {'linemate': 1}
        result = self.ai.drop_resources()
        expected_queue = ['Set linemate']
        self.assertEqual(result, expected_queue)

    def test_drop_resources_with_multiple_resource(self):
        self.ai.inventory = {'linemate': 2, 'food': 1}
        result = self.ai.drop_resources()
        expected_queue = ['Set linemate','Set linemate']
        self.assertEqual(result, expected_queue)

    def test_parse_input_list_empty_list(self):
        row_list = '[]'
        result = self.ai._parse_input_list(row_list)
        self.assertEqual(result, [[]])

    def test_parse_input_list_with_spaces(self):
        row_list = '[1, 2, 3, 4]'
        result = self.ai._parse_input_list(row_list)
        expected_list = [['1'], ['2'], ['3'], ['4']]
        self.assertEqual(result, expected_list)

    def test_has_not_resources(self):
        self.ai.inventory = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.assertFalse(self.ai.has_all_resources())


    def test_reset_direction_default(self):
        self.ai.direction = 'Up'
        self.ai.reset_direction()
        self.assertEqual(self.ai.direction, 'Down')

    def test_reset_direction_already_down(self):
        self.ai.direction = 'Down'
        self.ai.reset_direction()
        self.assertEqual(self.ai.direction, 'Down')

    def test_move_direction(self):
        goal_direction = 'Left'
        self.ai.move_direction(goal_direction)
        self.assertEqual(self.ai.queue, ['Left', 'Forward'])


    def test_move_to_same_position(self):
        self.ai.x = 5
        self.ai.y = 5
        self.ai.move_to(5, 5)
        self.assertEqual(self.ai.queue, [])

    def test_has_all_resources(self):
        self.ai.inventory =  {"linemate": 100, "deraumere": 100, "sibur": 100, "mendiane": 100, "phiras": 100, "thystame": 100}
        result = self.ai.take_resources_to_get()
        self.assertTrue(result)
        self.assertEqual(self.ai.inventory['sibur'], 100)



    #def test_algorithm_level1(self):
    #    input_message = "[ food player, sibur, deraumere linemate, mendiane phiras ]"
    #    self.ai.inventory['food'] = 3
    #    parsed_vision = self.ai.parse_vision(input_message)
    #    if self.ai.mode == 'Normal':
    #        result = self.ai.algorithm()
    #    self.assertTrue('Left', result)

    def test_inventory_update(self):
        self.assertEqual(self.ai.update_state('look'), 1)


class TestClient(unittest.TestCase):
    def setUp(self):
        self.host = '127.0.0.1'
        self.port = 8080
        self.name = 'team1'
        self.client = Client(self.host, self.port, self.name)


    def test_connect(self):
        value = self.client.connect()
        self.assertEqual(value, 0)


    def test_send_true(self):
        self.assertEqual(self.client.send(self.name), 84)

    def test_send_false(self):
        self.assertEqual(self.client.send(self.port), 84)

    def test_receive(self):
        self.client.send(self.name)
        response = self.client.receive()
        self.assertNotEqual(response, "ko")

    def test_send_queue_empty(self):
        self.client.queue = []
        self.client.send_queue()
        self.assertEqual(self.client.queue, [])



if __name__ == '__main__':
    unittest.main()
