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

# --------------------------------------------- DRIVING MODE
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
# axs[1, 0].plot(time_values, power_driving_values)
# axs[1, 0].set_title('Power in Driving Mode against Time')
# axs[1, 1].plot(time_values,power_driving_values)
# axs[1, 1].set_title('Power in Driving Mode against Time')

# for ax in axs.flat:
#     ax.set(xlabel='Time in Seconds', ylabel='Power in Watts')
# # Hide x labels and tick labels for top plots and y ticks for right plots.
# for ax in axs.flat:
#     ax.label_outer()

plt.show()
# ----------------------Graph of power against Velocity --------------




# 2. Power required to maintain the tractor at top speed in driving mode
power_driving_2 = traction_force * tractor_top_speed_mps



