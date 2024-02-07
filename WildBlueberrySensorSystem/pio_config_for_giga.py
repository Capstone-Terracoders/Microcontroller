# Description: This script is used for versions of PlatformIO Core that does not natively support the Giga board.
#   It adds the Giga board to the ST STM32 platform and updates the Arduino core for Mbed OS to include the Giga board.
#   The script also updates the ST STM32 platform to include the Giga board.
#   The script should be run in the PlatformIO Core environment.
import os
import json
import fileinput

# Define the directory path
directory = os.path.join(os.getenv('USERPROFILE'), '.platformio', 'platforms', 'ststm32', 'boards')

# Define the file path
file_path = os.path.join(directory, 'giga.json')

# JSON data to add
data_to_add = {
    "build": {
        "arduino": {
            "ldscript": "linker_script.ld",
            "flash_layout": "100_0"
        },
        "extra_flags": "-DARDUINO_GIGA -DARDUINO_GIGA_PINS -DGIGA_PINS -DGIGA -DCM4_BINARY_START=0x60000000 -DCM4_BINARY_END=0x60040000 -DCM4_RAM_END=0x60080000",
        "core": "arduino",
        "cpu": "cortex-m7",
        "f_cpu": "480000000L",
        "mcu": "stm32h747xih6",
        "variant": "GIGA",
        "product_line": "STM32H747xx",
        "hwids": [
            [
                "0x2341",
                "0x0366"
            ],
            [
                "0x2341",
                "0x0266"
            ],
            [
                "0x2341",
                "0x0466"
            ]
        ]
    },
    "connectivity": [
        "bluetooth",
        "wifi"
    ],
    "debug": {
        "jlink_device": "STM32H747XI_M7",
        "openocd_target": "stm32h7x_dual_bank"
    },
    "frameworks": [
        "arduino"
    ],
    "name": "Arduino Giga R1 Wifi",
    "upload": {
        "maximum_ram_size": 523624,
        "maximum_size": 1966080,
        "protocol": "dfu",
        "protocols": [
            "cmsis-dap",
            "dfu",
            "jlink",
            "stlink",
            "mbed"
        ],
        "require_upload_port": True,
        "use_1200bps_touch": True,
        "wait_for_upload_port": True,
        "offset_address": "0x08040000"
    },
    "url": "https://docs.arduino.cc/hardware/giga-r1-wifi",
    "vendor": "Arduino"
}

# Check if the directory exists, if not, create it
if not os.path.exists(directory):
    os.makedirs(directory)

# Check if the file exists, if not, create it and add the data
if not os.path.exists(file_path):
    with open(file_path, 'w') as f:
        json.dump(data_to_add, f, indent=4)
    print("File created and data added successfully.")
else:
    # If the file already exists, load the existing data and update it with new data
    print("File already exists. Data not added.")
    # print("Data added to existing file successfully.")



# Update the file ARDUINO for giga:

# Define the directory path
directory = os.path.join(os.getenv('USERPROFILE'), '.platformio', 'platforms', 'ststm32', 'builder', 'frameworks', 'arduino', 'mbed-core')

file_name = 'arduino-core-mbed.py'
# Define the file path
file_path = os.path.join(directory, file_name)

# Define the lines to be replaced and the replacement lines
old_lines = [
    '    if not board_id.startswith(("portenta_h7", "opta", "nicla_vision")):\n',
    '        if board_id in ("portenta_h7_m4", "opta_m4", "nicla_vision_m4"):\n',
    '            if board_id in ("portenta_h7_m4", "opta_m4", "nicla_vision_m4"):\n',
    '        if board_id in("portenta_h7_m4", "giga_r1_m4"):\n',
]
new_lines = [
    '    if not board_id.startswith(("portenta_h7", "opta", "nicla_vision", "giga")):\n',
    '        if board_id in ("portenta_h7_m4", "opta_m4", "nicla_vision_m4", "giga_r1_m4"):\n',
    '            if board_id in ("portenta_h7_m4", "opta_m4", "nicla_vision_m4", "giga_r1_m4"):\n',
    '        if board_id in("portenta_h7_m4", "giga_r1_m4"):\n',
]

# Perform the replacement
with fileinput.FileInput(file_path, inplace=True, backup='.bak') as file:
    for line in file:
        for old, new in zip(old_lines, new_lines):
            if line.strip() == old.strip():
                line = new
        print(line, end='')

print(f"File '{file_name}' modified successfully.")

###### 
# Update STSTM32 platform.py:
######
# Define the directory path
directory = os.path.join(os.getenv('USERPROFILE'), '.platformio', 'platforms', 'ststm32')

file_name = 'platform.py'
# Define the file path
file_path = os.path.join(directory, file_name)

# Define the line to be replaced and the replacement line
old_line = 'if board.startswith(("portenta", "opta", "nicla_vision")):\n'
new_line = 'if board.startswith(("portenta", "opta", "nicla_vision", "giga")):\n'

# Perform the replacement
with fileinput.FileInput(file_path, inplace=True, backup='.bak') as file:
    for line in file:
        # Check if the line matches the old line without considering leading/trailing whitespace
        if line.strip() == old_line.strip():
            # Dynamically determine leading whitespace from the existing line
            leading_whitespace = line[:len(line) - len(line.lstrip())]
            # Apply the leading whitespace to the replacement line
            line = leading_whitespace + new_line.lstrip()
        print(line, end='')

print(f"File '{file_name}' modified successfully.")