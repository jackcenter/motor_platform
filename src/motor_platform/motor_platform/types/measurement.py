from motor_platform.types.header import Header


class Measurement:
    def __init__(self, header: Header, encoder_1_pos: int, encoder_2_pos: int):
        self.header = header
        self.encoder_1_pos = encoder_1_pos
        self.encoder_2_pos = encoder_2_pos

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__

        return False

    @staticmethod
    def create_from_json(obj):
        return Measurement(
            header=Header.create_from_json(obj["header"]),
            encoder_1_pos=obj["encoder_1_pos"],
            encoder_2_pos=obj["encoder_2_pos"],
        )
