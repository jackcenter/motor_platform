import motor_platform.utilities.json_utilities as json_utils

import json
import unittest

from motor_platform.types.timestamp import Timestamp


class TestJsonUtilities(unittest.TestCase):

    def test_timestamp_decoder(self):
        timestamp_json_string = '{"timestamp":{"microseconds":1}}'
        timestamp_from_json = json.loads(
            timestamp_json_string, cls=json_utils.TimestampDecoder
        )

        expected_timestamp = Timestamp(microseconds=1)
        self.assertEqual(expected_timestamp, timestamp_from_json)

    def test_timestamp_encoder(self):
        timestamp = Timestamp(microseconds=1)
        timestamp_json_string = json.dumps(
            timestamp, cls=json_utils.TimestampEncoder, separators=(",", ":")
        )

        expected_json_sting = '{"timestamp":{"microseconds":1}}'
        self.assertEqual(expected_json_sting, timestamp_json_string)
