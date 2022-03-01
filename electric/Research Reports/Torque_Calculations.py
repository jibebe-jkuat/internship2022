from math import pi


maximum_load_power = 500          # in watts
diameter_of_wheel = 0.5     # in metres
circumference_of_wheel = pi * diameter_of_wheel
distance_covered_by_wheel = circumference_of_wheel          # in one rev
maximum_speed_of_tricycle = 4.5   # in m/s
speed_in_rpm = (maximum_speed_of_tricycle / distance_covered_by_wheel) * 60


large_sprocket_radius = 0.02421      # in m
small_sprocket_radius = 0.0875     # in m

# ----------------large sprocket parameters------------------
angular_velocity = (2 * pi * speed_in_rpm) / 60
velocity = angular_velocity * large_sprocket_radius

# -----------------small sprocket parameters-----------------
angular_velocity = velocity / small_sprocket_radius
torque = maximum_load_power / angular_velocity

print("Required Torque is ", torque)
