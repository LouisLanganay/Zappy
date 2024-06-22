import unittest
from unittest.mock import patch, MagicMock
from Main import ParseArgs
from Main import MainClient
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

    def test_print_usage(self):
        with patch('sys.exit') as mock_exit:
            self.obj.print_usage()
            mock_exit.assert_called_with(84)


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

    def test_parse_help_argument(self):
        args = ['-help']
        with patch('sys.exit') as mock_exit:
            self.obj.parse(args)
            mock_exit.assert_called_with(0)

    def test_parse_invalid_port_type(self):
        args = ['-p', 'invalid', '-n', 'validname', '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_port_out_of_range(self):
        args = ['-p', 70000, '-n', 'validname', '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_name_too_long(self):
        long_name = 'a' * 33  # 33 characters long
        args = ['-p', 8080, '-n', long_name, '-h', 'localhost']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_parse_invalid_host(self):
        args = ['-p', 8080, '-n', 'validname', '-h', 'invalid_host']
        result = self.obj.parse(args)
        self.assertEqual(result, 84)

    def test_print_usage(self):
        with patch('sys.exit') as mock_exit:
            self.assertEqual(self.obj.print_usage(), 84)

    def test_print_invalid_argument(self):
        with patch('builtins.print') as mock_print:
            self.assertEqual(self.obj.print_invalid_argument(), 84)
            mock_print.assert_called_with("Invalid argument")





#class TestMainClient(unittest.TestCase):
#
#    def setUp(self):
#        self.host = 'localhost'
#        self.port = 8080
#        self.name = 'test_client'
#        self.client = MainClient(self.host, self.port, self.name)

  #  def test_init(self, mock_socket):
  #      mock_socket.return_value.connect.return_value = None
  #      client = MainClient(self.host, self.port, self.name)

 #   def test_send(self, mock_socket):
 #       mock_socket_inst = mock_socket.return_value
 #       client = MainClient(self.host, self.port, self.name)
 #       client.send('data')
 #       mock_socket_inst.send.assert_called_with(b'data')
#
 #   def test_receive(self, mock_socket):
 #       mock_socket_inst = mock_socket.return_value
 #       mock_socket_inst.recv.return_value = b'data\n'
 #       client = MainClient(self.host, self.port, self.name)
 #       result = client.receive()
 #       self.assertEqual(result, 'data')
#
 #   def test_receive_no_data(self, mock_socket):
 #       mock_socket_inst = mock_socket.return_value
 #       mock_socket_inst.recv.return_value = b''
 #       client = MainClient(self.host, self.port, self.name)
 #       result = client.receive()
 #       self.assertEqual(result, 84)
#
 #   def test_connect_and_get_slots(self, mock_socket):
 #       mock_socket_inst = mock_socket.return_value
 #       mock_socket_inst.recv.side_effect = [b'Welcome\n', b'3\n']
 #       client = MainClient(self.host, self.port, self.name)
 #       result = client.connect_and_get_slots()
 #       self.assertEqual(result, 4)
#
 #   def test_close(self, mock_socket):
 #       mock_socket_inst = mock_socket.return_value
 #       client = MainClient(self.host, self.port, self.name)
 #       client.close()
 #       mock_socket_inst.close.assert_called_once()





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




class ClientTest(unittest.TestCase):

    @patch('socket.socket')
    def setUp(self, mock_socket):
        self.mock_socket_instance = mock_socket.return_value
        self.mock_socket_instance.recv.return_value = 'welcome\n'.encode()
        self.client = Client('127.0.0.1', 8080, 'team1')

    def test_send(self):
        self.client.send('Hello')
        self.mock_socket_instance.send.assert_called_with(b'Hello\n')

    @patch.object(Client, 'receive', return_value='message 1, Group')
    def test_receive(self, mock_receive):
        data = self.client.receive()
        self.assertEqual(data, 'message 1, Group')

    def test_update_inventory(self):
        with patch.object(Client, 'send') as mock_send, patch.object(Client, 'receive', return_value='Inventory data'):
            self.client.update_inventory()
            mock_send.assert_called_with('Inventory')
            self.client.ai.update_state.assert_called_with('Inventory data')

    def test_update_vision(self):
        with patch.object(Client, 'send') as mock_send, patch.object(Client, 'receive', return_value='Vision data'):
            self.client.update_vision()
            mock_send.assert_called_with('Look')
            self.client.ai.update_state.assert_called_with('Vision data')

    def test_send_queue(self):
        self.client.queue = ['Command1', 'Command2']
        with patch.object(Client, 'send') as mock_send, patch.object(Client, 'receive', return_value='ok'):
            self.client.send_queue()
            self.assertEqual(mock_send.call_count, 2)
            self.assertEqual(self.client.queue, [])

    def test_handle_broadcast(self):
        message = 'message 1, Group'
        self.client.handle_broadcast(message)
        self.assertEqual(self.client.ai.mode, 'Group')
        self.assertEqual(self.client.ai.broadcaster_direction, 1)

    def test_connect(self):
        with patch.object(Client, 'send') as mock_send, patch.object(Client, 'receive', return_value='map size'):
            self.client.connect()
            mock_send.assert_called_with('test_client')

    def tearDown(self):
        self.client.close()



if __name__ == '__main__':
    unittest.main()
