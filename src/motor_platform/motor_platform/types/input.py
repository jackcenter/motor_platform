from motor_platform.types.header import Header


class Input:
    def __init__(self, header: Header, voltage: float):
        self.header = header
        self.voltage = voltage

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__

        return False

    @staticmethod
    def create_from_json(obj):
        return Input(
            header=Header.create_from_json(obj["header"]), voltage=obj["voltage"]
        )
