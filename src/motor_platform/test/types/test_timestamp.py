from motor_platform.types.timestamp import Timestamp

import unittest


class TestTimestamp(unittest.TestCase):

    def test_timestamp_equivalency(self):
        timestamp = Timestamp(microseconds=1)

        self.assertFalse(timestamp == 1)

        equivalent_timestamp = Timestamp(microseconds=1)
        self.assertTrue(timestamp == equivalent_timestamp)
        self.assertFalse(timestamp != equivalent_timestamp)

        inequivalent_timestamp = Timestamp(microseconds=2)
        self.assertFalse(timestamp == inequivalent_timestamp)
        self.assertTrue(timestamp != inequivalent_timestamp)
