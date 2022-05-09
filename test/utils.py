from typing import Tuple


def interpolate(
    value: float, value_range: Tuple[float, float], output_range: Tuple[float, float]
):
    value_range_span = float(value_range[1] - value_range[0])
    output_range_span = float(output_range[1] - output_range[0])
    value_scaled = float(value - value_range[0]) / value_range_span
    return float(output_range[0]) + (value_scaled * output_range_span)
