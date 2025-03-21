import json
import os
import shutil
import fnmatch
import subprocess
from pathlib import Path

class ConfigType:
    def __init__(self, name: str, description: str, validation, from_string):
        self.name = name
        self.description = description
        self.validation = validation
        self.from_string_fn = from_string

    def validate(self, value) -> bool:
        return self.validation(value)

    def from_string(self, value) -> tuple:
        try:
            return (self.from_string_fn(value), None)
        except Exception as e:
            return (False, e)

class ConfigValue:
    def __init__(self, name: str, description: str, type: str, default_value):
        self.name = name
        self.description = description
        self.type = type
        self.default_value = default_value

EXCLUDED_CLEAN_FILES = [
    "*.bat",
    "*.sh",
    "*.json",
    "*.py",
    "resources",
]
CMAKE_BINARY = "cmake"
CURRENT_DIR = Path(__file__).resolve().parent
PROJECT_DIR = CURRENT_DIR.parent
BUILD_DIR = os.path.join(PROJECT_DIR, 'build')
ORIGINAL_BUILD_DIR = BUILD_DIR # Copy the original build directory
BINARY_DIR = os.path.join(BUILD_DIR, 'bin')
CONFIG_TYPES = {
    "string": ConfigType("string", "A string value", lambda _: True, lambda x: x),
    "generator": ConfigType("generator", "A CMake generator", lambda x: x in ["Ninja", "Unix Makefiles", "Visual Studio 17 2022", "Xcode"], lambda x: x),
    "build_type": ConfigType("build_type", "A build type", lambda x: x in ["Debug", "Release", "RelWithDebugInfo"], lambda x: x),
    "boolean": ConfigType("boolean", "A boolean value", lambda x: x in ["true", "false", True, False], lambda x: x == "true" or x == True),
    "path": ConfigType("path", "A path", lambda x: os.path.exists(x), lambda x: x),
    "library_type": ConfigType("library_type", "The type of library to build", lambda x: x in ["shared", "static"], lambda x: x.upper()),
    "simd_type": ConfigType("simd_type", "The SIMD type to use", lambda x: x in ["None", "SSE4.1", "AVX"], lambda x: x),
}
CONFIG_VALUES = {
    "cmake_generator": ConfigValue("cmake_generator", "The CMake generator to use", "generator", "Ninja"),
    "build_type": ConfigValue("build_type", "The build type to use", "build_type", "Debug"),
    "library_type": ConfigValue("library_type", "The type of library to build", "library_type", "shared"),
    "compile_commands": ConfigValue("compile_commands", "Generate compile_commands.json", "boolean", "true"),
    "simd_type": ConfigValue("simd_type", "The SIMD type to use", "simd_type", "None"),
    "executable_files": [ConfigValue("executable_files", "The files to build as executables", "string", "main.cpp")], # We use this to tell it that it is an array
}

def safe_get_input(prompt: str, default_value: str) -> tuple[str, bool]:
    try:
        value = input(f'{prompt} [{default_value}]: ').strip()
    except KeyboardInterrupt:
        print('Input cancelled. ')
        return (default_value, False)
    if value == '':
        return (default_value, True)
    return (value, True)

print("Building... (Directory: {})".format(CURRENT_DIR))

# Create the configuration file if it does not exist
config_file = os.path.join(CURRENT_DIR, 'config.json')
if not os.path.exists(config_file):
    print('Configuration file not found. Creating a new one.')
    name,success = safe_get_input('Enter profile name', 'Default')
    if not success:
        exit(1)
    prof = {}

    for key, value in CONFIG_VALUES.items():
        value, success = safe_get_input(f'Enter {value.description}', value.default_value)
        if not success:
            exit(1) # Exit if the user cancels the input
        prof[key] = value

    config = {
        "profiles": {
            name: prof
        },
        "last_profile": None
    }

    print('Writing configuration file...')
    try:
        json.dump(config, open(config_file, 'w'), indent=4)
    except Exception as e:
        print(f'Error writing configuration file: {e}')
        exit(1)

# Read the configuration file
with open(config_file) as f:
    try:
        config = json.load(f)
    except Exception as e:
        print(f'Error reading configuration file: {e}')
        exit(1)

# We make sure that the configuration file is not empty
if not config:
    print('Configuration file is empty. Exiting...')
    exit(1)

# We parse each profile in the configuration file and make sure that the values are valid and have all the required keys
for profile_name, prof in config['profiles'].items():
    for key, value in CONFIG_VALUES.items():
        if key not in prof:
            print(f'Profile {profile_name} is missing key {key}. \n{value.description}. \nExiting..')
            exit(1)
        if type(value) == list:
            for i, val in enumerate(prof[key]):
                if not CONFIG_TYPES[value[0].type].validate(val):
                    print(f'Profile {profile_name} has an invalid value for key {key}. \n{value[0].description}. \nExiting...')
                    exit(1)
            continue
        if not CONFIG_TYPES[value.type].validate(prof[key]):
            print(f'Profile {profile_name} has an invalid value for key {key}. \n{value.description}. \nExiting...')
            exit(1)

# We make sure that the last profile is valid
if config['last_profile'] not in config['profiles']:
    print(f'Last profile {config["last_profile"]} is not a valid profile. Select another profile...')
    config['last_profile'] = None # We reset the last profile to None
else:
    inp, success = safe_get_input(f'Use last profile {config["last_profile"]}?', "Y")
    if not success:
        print('Invalid Input. Exiting...')
        exit(1)
    if not inp.lower().startswith('y'):
        config['last_profile'] = None

ACTIONS = {
    "build": "Build the project",
    "run": "Run the project",
    "clean": "Clean the build directory",
    "configure": "Configure the project",
    "exit": "Exit the program",

}

for i, (key, value) in enumerate(ACTIONS.items()):
    print(f'{i+1}. {value}')

try:
    action,success = safe_get_input('Select an action', 'build')

    if not success:
        print('Invalid action. Exiting...')
        exit(1)

    try:
        action = int(action)
        if action < 1 or action > len(ACTIONS):
            print('Invalid action. Exiting...')
            exit(1)
        action = list(ACTIONS.keys())[action-1]
    except ValueError:
        pass

    if action not in ACTIONS:
        print('Invalid action. Exiting...')
        exit(1)

except KeyboardInterrupt:
    print('Exiting...')
    exit(0)

if action == 'exit':
    print('Exiting...')
    exit(0)

if not config['last_profile']:
    profiles = list(config['profiles'].keys())
    print('No profile selected. Select a profile to continue...')
    for i, profile in enumerate(profiles):
        print(f'{i+1}. {profile}')

    profile, success = safe_get_input('Select a profile', profiles[0])
    if not success:
        print('Invalid profile. Exiting...')
        exit(1)
    try:
        prof = int(profile)
        if prof < 1 or prof > len(profiles):
            print('Invalid profile. Exiting...')
            exit(1)
        profile = profiles[prof-1]
    except ValueError:
        pass
    if profile not in profiles:
        inp, success = safe_get_input('Invalid profile. Create profile?', "Y")
        if not success:
            print('Invalid Input. Exiting...')
            exit(1)
        if inp.lower().startswith('y'):
            profile, success = safe_get_input('Enter profile name', profile)
            if not success:
                exit(1)
            config['profiles'][profile] = {}
            for key, value in CONFIG_VALUES.items():
                value, success = safe_get_input(f'Enter {value.description}', value.default_value)
                if not success:
                    exit(1)
                config['profiles'][profile][key] = value

    config['last_profile'] = profile
    json.dump(config, open(config_file, 'w'), indent=4)
else:
    profile: str = config['last_profile']

# We set the build dir to append the profile name as a subdirectory
BUILD_DIR = os.path.join(BUILD_DIR, profile)

# Create the build directory if it does not exist
if not os.path.exists(BUILD_DIR):
    os.makedirs(BUILD_DIR)

if action == 'clean':
    print('Cleaning the build directory...')

    for file in os.listdir(BUILD_DIR):
        exclude = False
        for pattern in EXCLUDED_CLEAN_FILES:
            if fnmatch.fnmatch(file, pattern):
                exclude = True
                break
        if exclude:
            continue

        file_path = os.path.join(BUILD_DIR, file)
        try:
            if os.path.isdir(file_path):
                print(f'Removing directory {file_path}...', end=' ')
                shutil.rmtree(file_path)
                print('Done')
            else:
                print(f'Removing file {file_path}...', end=' ')
                os.remove(file_path)
                print('Done')
        except Exception as e:
            print(f'Error: {e}')
    print('Done')
    exit(0)

# We need a profile to continue

def get_profile_config(profile: str, key: str):
    cfg,ex= CONFIG_TYPES[CONFIG_VALUES[key].type].from_string(config['profiles'][profile][key])
    if ex:
        print(f'Error: {ex}')
        exit(1)
    return cfg

if action == 'configure':
    print('Configuring the project...')
    generator = get_profile_config(profile, 'cmake_generator')
    build_type = get_profile_config(profile, 'build_type')
    library_type = get_profile_config(profile, 'library_type')
    compile_commands = "ON" if get_profile_config(profile, 'compile_commands') else "OFF"
    simd_type = get_profile_config(profile, 'simd_type')

    print('Generating with types:')
    for key, value in CONFIG_VALUES.items():
        if type(value) == list:
            continue
        print(f'{value.name}: {config["profiles"][profile][key]}')

    cmd = f'{CMAKE_BINARY} -G "{generator}" -DCMAKE_BUILD_TYPE={build_type} -DPULSARION_LIBRARY_TYPE={library_type} -DCMAKE_EXPORT_COMPILE_COMMANDS={compile_commands} -DPULSARION_SIMD={simd_type} -S {PROJECT_DIR} -B {BUILD_DIR}'
    print(f'Running command: {cmd}')
    os.system(cmd)

    if compile_commands == "ON":
        print('Copying compile_commands.json to project root...', end=' ')
        try:
            shutil.copy(os.path.join(BUILD_DIR, 'compile_commands.json'), os.path.join(PROJECT_DIR, 'compile_commands.json'))
            print('Done')
        except Exception as e:
            print(f'Error: {e}')

    exit(0)

if action == 'build':
    print('Building the project...')
    os.system(f'{CMAKE_BINARY} --build {BUILD_DIR}')
    exit(0)

if action == 'run':
    files = []
    for file in config['profiles'][profile]['executable_files']:
        files.append(file)

    if not files:
        print('No executable files found. Exiting...')
        exit(1)

    for index,file in enumerate(files):
        print(f'{index+1}. {file}')

    inp, success = safe_get_input('Select an executable', files[0])
    if not success:
        print('Invalid input. Exiting...')
        exit(1)

    file = None
    try:
        f = int(inp)
        if f < 1 or f > len(files):
            print('Invalid input. Exiting...')
            exit(1)
        file = files[f-1]
    except ValueError:
        for f in files:
            if f == inp:
                file = inp
                break
    if not file:
        print('Invalid input. Exiting...')
        exit(1)

    print(f'Running {file}...')
    path = os.path.join(BUILD_DIR, file)
    try:
        result = subprocess.run(path,
                        cwd=f"{ORIGINAL_BUILD_DIR}",  # Set your working directory
                        stdin=None,                  # Use the parent's stdin
                        text=True)
        print("Exit code:", result.returncode)
    except KeyboardInterrupt:
        print('Exiting...')
    except Exception as e:
        print(f'Error: {e}')

    exit(0)
