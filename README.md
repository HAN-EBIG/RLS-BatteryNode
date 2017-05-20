# RLS-BatteryNode
The code for a sensornode that measures its battery level and sends it over to a MS gateway...

# Configuration

(1) PERCENTAGE_TOP_MARGE its possible a fully charged battery can be a little more than 100%, for example a 9v battery has an output of 9.2 voltage, give a maximum marge in percentages before you assume the calculation went wrong. For example 110% (will be send as 100%)
(2) PERCENTAGE_MIN_MARGE same, but than for minimum marge
(3) INPUT_VOLTAGE_MC 1.1v, 3v, 3.3v, 5v
