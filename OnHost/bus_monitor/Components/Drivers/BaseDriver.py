from abc import ABC, abstractmethod

from Components.models.can_frame import CanFrame


class BaseDriver(ABC):
    @abstractmethod
    def open(self) -> None:
        pass

    @abstractmethod
    def close(self) -> None:
        pass

    @abstractmethod
    def send(self, frame: CanFrame) -> None:
        pass
