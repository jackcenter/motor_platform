import motor_platform.utilities.json_utilities as json_utils

import json
import unittest

from motor_platform.types.header import Header
from motor_platform.types.input import Input
from motor_platform.types.measurement import Measurement
from motor_platform.types.state import State
from motor_platform.types.timestamp import Timestamp


class TestJsonUtilities(unittest.TestCase):

    def test_timestamp_decoder(self):
        timestamp_json_string = '{"timestamp":{"microseconds":1}}'
        timestamp_json = json.loads(timestamp_json_string)

        expected_timestamp = Timestamp(microseconds=1)
        timestamp_from_json = Timestamp.create_from_json(timestamp_json["timestamp"])
        self.assertEqual(expected_timestamp, timestamp_from_json)

    def test_timestamp_encoder(self):
        timestamp = Timestamp(microseconds=1)
        timestamp_json_string = json.dumps(
            timestamp, cls=json_utils.TimestampEncoder, separators=(",", ":")
        )

        expected_timestamp_json_string = '{"microseconds":1}'
        self.assertEqual(expected_timestamp_json_string, timestamp_json_string)

    def test_header_decoder(self):
        header_json_string = '{"header":{"sequence":0,"timestamp":{"microseconds":1}}}'
        header_json = json.loads(header_json_string)

        expected_header = Header(sequence=0, timestamp=Timestamp(microseconds=1))
        header_from_json = Header.create_from_json(header_json["header"])
        self.assertEqual(expected_header, header_from_json)

    def test_header_encoder(self):
        header = Header(sequence=0, timestamp=Timestamp(microseconds=1))
        header_json_string = json.dumps(
            header, cls=json_utils.HeaderEncoder, separators=(",", ":")
        )

        expected_header_json_string = '{"sequence":0,"timestamp":{"microseconds":1}}'
        self.assertEqual(expected_header_json_string, header_json_string)

    def test_input_decoder(self):
        input_json_string = '{"input":{"header":{"sequence":0,"timestamp":{"microseconds":1}},"voltage":2.0}}'
        input_json = json.loads(input_json_string)

        expected_input = Input(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)), voltage=2.0
        )
        input_from_json = Input.create_from_json(input_json["input"])
        self.assertEqual(expected_input, input_from_json)

    def test_input_encoder(self):
        input = Input(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)), voltage=2.0
        )
        input_json_string = json.dumps(
            input, cls=json_utils.InputEncoder, separators=(",", ":")
        )

        expected_input_json_string = (
            '{"header":{"sequence":0,"timestamp":{"microseconds":1}},"voltage":2.0}'
        )
        self.assertEqual(expected_input_json_string, input_json_string)

    def test_measurement_decoder(self):
        measurement_json_string = '{"measurement":{"header":{"sequence":0,"timestamp":{"microseconds":1}},"encoder_1_pos":2,"encoder_2_pos":3}}'
        measurement_json = json.loads(measurement_json_string)

        expected_measurement = Measurement(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)),
            encoder_1_pos=2,
            encoder_2_pos=3,
        )
        measurement_from_json = Measurement.create_from_json(
            measurement_json["measurement"]
        )
        self.assertEqual(expected_measurement, measurement_from_json)

    def test_measurement_encoder(self):
        measurement = Measurement(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)),
            encoder_1_pos=2,
            encoder_2_pos=3,
        )
        measurement_json_string = json.dumps(
            measurement, cls=json_utils.MeasurementEncoder, separators=(",", ":")
        )

        expected_measurement_json_string = '{"header":{"sequence":0,"timestamp":{"microseconds":1}},"encoder_1_pos":2,"encoder_2_pos":3}'
        self.assertEqual(expected_measurement_json_string, measurement_json_string)

    def test_state_decoder(self):
        state_json_string = '{"state":{"header":{"sequence":0,"timestamp":{"microseconds":1}},"joint_1_position_rad":2.0,"joint_1_velocity_rps":3.0,"joint_2_position_rad":4.0,"joint_2_velocity_rps":5.0}}'
        state_json = json.loads(state_json_string)

        expected_state = State(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)),
            joint_1_position_rad=2.0,
            joint_1_velocity_rps=3.0,
            joint_2_position_rad=4.0,
            joint_2_velocity_rps=5.0,
        )
        state_from_json = State.create_from_json(state_json["state"])
        self.assertEqual(expected_state, state_from_json)

    def test_state_encoder(self):
        state = State(
            header=Header(sequence=0, timestamp=Timestamp(microseconds=1)),
            joint_1_position_rad=2.0,
            joint_1_velocity_rps=3.0,
            joint_2_position_rad=4.0,
            joint_2_velocity_rps=5.0,
        )
        state_json_string = json.dumps(
            state, cls=json_utils.StateEncoder, separators=(",", ":")
        )

        expected_state_json_string = '{"header":{"sequence":0,"timestamp":{"microseconds":1}},"joint_1_position_rad":2.0,"joint_1_velocity_rps":3.0,"joint_2_position_rad":4.0,"joint_2_velocity_rps":5.0}'
        self.assertEqual(expected_state_json_string, state_json_string)
