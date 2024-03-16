from typing import NamedTuple

class Timestamp(NamedTuple):
    microseconds: int 


    @staticmethod
    def decode(json_value):
        return Timestamp(microseconds=json_value["microseconds"])
