from dataclasses import dataclass
from queue import Queue


@dataclass
class Sesnor:

    data: Queue[float]

    min_threshold: float
    max_threshold: float
    is_ready: bool
    increase_threshold: float

    target_temperature: float | None

    target_accuracy = 1.0
    max_queue_size = 3.0

    def __post_init__(
        self,
        data: list,
        min_threshold_temperature: float,
        max_threshold_temperature: float,
        is_ready: bool,
        target_temperature: float | None = None,
    ) -> None:
        self.data = Queue(maxsize=self.max_queue_size)
        self.min_threshold_temperature = min_threshold_temperature
        self.max_threshold_temperature = max_threshold_temperature
        self.is_ready = is_ready
        self.target_temperature = target_temperature

        for reading in data:
            self.data.put(reading)

    def add(self, temperature) -> None:
        self.data.put(temperature)
        self.data.dequeue()

        if self.target_temperature is not None and self.is_ready:
            if self.activate_alert():
                pass
            # send alert
        else:
            if self.data.full():
                delta1 = self.data.queue[1] - self.data.queue[0]
                delta2 = self.data.queue[2] - self.data.queue[1]

                eps = 0.1

                if delta1 - eps > 0 and delta2 - eps > 0:
                    self.is_ready = True
                    self.target_temperature = sum(self.data.queue) / self.max_queue_size
                    self.min_threshold_temperature = (
                        self.target_temperature - self.target_accuracy
                    )
                    self.max_threshold_temperature = (
                        self.target_temperature + self.target_accuracy
                    )

    def activate_alert(self) -> bool:
        if self.data.full():

            data_avg = sum(self.data.queue) / self.max_queue_size
            if (
                data_avg < self.min_threshold_temperature
                or data_avg > self.max_threshold_temperature
            ):
                return True

        return False
