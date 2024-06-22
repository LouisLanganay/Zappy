import unittest
from unittest.mock import patch
from Main import ParseArgs
from Main import MainClient

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








class TestMainClient(unittest.TestCase):
    def setUp(self):
        self.host = 'localhost'
        self.port = 8080
        self.name = 'test_client'
        self.client = MainClient(self.host, self.port, self.name)

    @patch('mainclient.socket.socket')
    def test_init(self, mock_socket):
        mock_socket.return_value.connect.return_value = None
        client = MainClient(self.host, self.port, self.name)
        mock_socket.return_value.connect.assert_called_with((self.host, self.port))

    @patch('mainclient.socket.socket')
    def test_send(self, mock_socket):
        mock_socket_inst = mock_socket.return_value
        client = MainClient(self.host, self.port, self.name)
        client.send('data')
        mock_socket_inst.send.assert_called_with(b'data')

    @patch('mainclient.socket.socket')
    def test_receive(self, mock_socket):
        mock_socket_inst = mock_socket.return_value
        mock_socket_inst.recv.return_value = b'data\n'
        client = MainClient(self.host, self.port, self.name)
        result = client.receive()
        self.assertEqual(result, 'data')

    @patch('mainclient.socket.socket')
    def test_receive_no_data(self, mock_socket):
        mock_socket_inst = mock_socket.return_value
        mock_socket_inst.recv.return_value = b''
        client = MainClient(self.host, self.port, self.name)
        result = client.receive()
        self.assertEqual(result, 84)

    @patch('mainclient.socket.socket')
    def test_connect_and_get_slots(self, mock_socket):
        mock_socket_inst = mock_socket.return_value
        mock_socket_inst.recv.side_effect = [b'Welcome\n', b'3\n']
        client = MainClient(self.host, self.port, self.name)
        result = client.connect_and_get_slots()
        self.assertEqual(result, 4)

    @patch('mainclient.socket.socket')
    def test_close(self, mock_socket):
        mock_socket_inst = mock_socket.return_value
        client = MainClient(self.host, self.port, self.name)
        client.close()
        mock_socket_inst.close.assert_called_once()





if __name__ == '__main__':
    unittest.main()
