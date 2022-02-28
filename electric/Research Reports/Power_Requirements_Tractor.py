import matplotlib.pyplot as plt


def convert_to_mps(speed):
    return speed * 0.278

# Specifications


top_speed = 11                 # in km/h
top_speed_mps = convert_to_mps(top_speed)
speed_at_rest = 0               # in m/s
time_taken = 8                  # in seconds. From rest to top speed
acceleration = (top_speed_mps - speed_at_rest) / time_taken

# Tractor
mass_of_tractor = 650           # in kg

# --------------------------------------------- DRIVING MODE------------------------------
# some considerations
tractor_top_speed = 30         # in km/h
tractor_top_speed_mps = convert_to_mps(tractor_top_speed)
rolling_coefficient = 0.01
gravitational_acceleration = 9.81  # in m/s^2

# 1. Power required to accelerate the tractor from rest to top speed in driving mode
# Accelerating force
accelerating_force = mass_of_tractor * acceleration
# Traction force
weight = mass_of_tractor * gravitational_acceleration
traction_force = rolling_coefficient * weight
# total force
total_force = accelerating_force + traction_force


# time required to accelerate from rest to top speed:
time = (tractor_top_speed_mps - speed_at_rest) / acceleration

# POWER
power_driving = total_force * acceleration * time

#Plot Graph of power_driving against time
time_values = [time - 8, time - 6, time - 4, time - 2, time, time + 2, time + 4, time + 6, time + 8]
velocity_values = []
power_driving_values = []
neg_power_driving_values = []
for i in time_values:
    power_driving_values.append(total_force*acceleration*i)
    neg_power_driving_values.append(- total_force * acceleration * i)
    velocity_values.append(acceleration*i)
# Graphs





fig, (ax1, ax2) = plt.subplots(1, 2)


ax1.plot(time_values, power_driving_values)
ax1.set_title('Power in Driving Mode against Time')
ax1.set(xlabel='Time in Seconds', ylabel='Power in Watts')
ax2.plot(velocity_values,  power_driving_values)
ax2.set_title('Power in Driving Mode against Velocity')
ax2.set(xlabel='Velocity in m/s', ylabel='Power in Watts')





# 2. Power required to maintain the tractor at top speed in driving mode
power_driving_2 = traction_force * tractor_top_speed_mps



# --------------------------------------------- WORKING MODE------------------------------


# Design considerations
tractor_top_speed_w = 11 # in km/h
tractor_top_speed_mps_w = convert_to_mps(tractor_top_speed_w)
rolling_coefficient_w = 0.09
specific_force = 280   # specific force of the plough on clay soil. Force/Unit width/cm depth
width_of_implement= 50 # in cm
depth_of_plough = 10 # in cm
traction_effiency = 80 # in percentage


# power required for accelerating the tractor from rest to top speed in working mode

draught_force = specific_force * (width_of_implement/100) * depth_of_plough

accelerating_force_w = mass_of_tractor * acceleration

traction_force_w = mass_of_tractor * gravitational_acceleration * rolling_coefficient

total_force_w = draught_force + accelerating_force_w + traction_force_w

time_w = tractor_top_speed_mps_w / acceleration

power_working = total_force_w * acceleration * time_w

# power required to maintain the tractor at top speed in working mode

total_force_w_2 = draught_force + traction_force_w


power_working_2 = total_force_w_2 * acceleration * time_w

#------------------------------------------------------Expected Load:

# first get maximum load power
maximum_load_power = power_working if power_working > power_working_2 else power_working_2

expected_load = maximum_load_power / (traction_effiency / 100)

print(expected_load) 
