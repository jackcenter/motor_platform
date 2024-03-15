class Timestamp:
    def __init__(self, microseconds: int):
        self.microseconds = microseconds

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__

        return False

    @staticmethod
    def create_from_json(obj):
        return Timestamp(microseconds=obj["microseconds"])
