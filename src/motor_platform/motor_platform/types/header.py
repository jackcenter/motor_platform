from motor_platform.types.timestamp import Timestamp


class Header:
    def __init__(self, sequence: int, timestamp: Timestamp):
        self.sequence = sequence
        self.timestamp = timestamp

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__

        return False

    @staticmethod
    def create_from_json(obj):
        return Header(
            sequence=obj["sequence"],
            timestamp=Timestamp.create_from_json(obj["timestamp"]),
        )
