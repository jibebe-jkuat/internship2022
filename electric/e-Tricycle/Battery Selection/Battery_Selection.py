power_rating_of_load = 600    # in watts
voltage_rating_of_motor = 48    # in volts

ampere_rating_of_motor = power_rating_of_motor / voltage_rating_of_motor
# acceleration current
# consider extra percentage
acceleration_percentage = 0.05
ampere_rating_of_motor *= (1+acceleration_percentage)



running_time = 2   # in hours
amperes_hours = ampere_rating_of_motor * running_time

state_of_charge = 40   # in percentage
depth_of_discharge = 100 - state_of_charge

amperes_hours = amperes_hours * (100 / depth_of_discharge)


efficiency_of_motor = 85   # in percentage
efficiency_of_battery = 85  # in percentage

amperes_hours = amperes_hours / (efficiency_of_battery * efficiency_of_motor / 10000)



print('Specifications.......')
print("Power rating of motor(W): ", power_rating_of_motor, " Voltage rating of motor(V): ", voltage_rating_of_motor)
print("Running time(hrs): ", running_time)
print("State of charge(in percentage): ", state_of_charge)
print("Efficiency of motor: ", efficiency_of_motor, " Efficiency of Battery: ", efficiency_of_battery)
print("Results...")
print('Required Voltage(V): ', voltage_rating_of_motor, " Required Current(Ah): ", amperes_hours)
