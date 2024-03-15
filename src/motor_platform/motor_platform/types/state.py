from motor_platform.types.header import Header


class State:
    def __init__(
        self,
        header: Header,
        joint_1_position_rad: float,
        joint_1_velocity_rps: float,
        joint_2_position_rad: float,
        joint_2_velocity_rps: float,
    ):
        self.header = header
        self.joint_1_position_rad = joint_1_position_rad
        self.joint_1_velocity_rps = joint_1_velocity_rps
        self.joint_2_position_rad = joint_2_position_rad
        self.joint_2_velocity_rps = joint_2_velocity_rps

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__

        return False

    @staticmethod
    def create_from_json(obj):
        return State(
            header=Header.create_from_json(obj["header"]),
            joint_1_position_rad=obj["joint_1_position_rad"],
            joint_1_velocity_rps=obj["joint_1_velocity_rps"],
            joint_2_position_rad=obj["joint_2_position_rad"],
            joint_2_velocity_rps=obj["joint_2_velocity_rps"],
        )
