import os, shutil

pwd = "/Users/isabelkaspriskie/Documents/Max 8/Packages/airfx/"
projects_dir = pwd + "source/projects/"
airwindows_dir = pwd + "source/airwindows/plugins/LinuxVST/src/"
plugin = "ToTape6"
meta = {
    "description": "tape emulation",
    "classname": plugin.lower()
}


def get_param_info():
    result = {}
    num_params = 0;
    num_inlets = 0;
    num_outlets = 0;

    # Open *.h
    lines = []
    with open(airwindows_dir + plugin + "/" + plugin + ".h") as f:
        lines = f.readlines()
    for line in lines:
        if "kNumParameters" in line:
            num_params = int(line.split(" ")[-1])
        elif "kNumInputs" in line:
            num_inlets = int(line.split(" ")[-1].split(";")[0])
        elif "kNumOutputs" in line:
            num_outlets = int(line.split(" ")[-1].split(";")[0])
    
    result["num_params"] = num_params
    result["num_ins"] = num_inlets
    result["num_outs"] = num_outlets
    result["attrs"] = []

    # Get default values from *.cpp constructor
    with open(airwindows_dir + plugin + "/" + plugin + ".cpp") as f:
        lines = f.readlines()
    
    index = 1
    for line in lines:
        index += 1
        if "AudioEffectX(" in line:
            break
    
    for i in range(num_params):
        initializer = lines[index + i].split("=")
        var = initializer[0].strip()
        val = initializer[1].split(";")[0].strip()
        result["attrs"].append({"variable": var, "initial_val": val})

    # Get name from *.cpp getParameterName()
    index = 1
    for line in lines:
        index += 1
        if "::getParameterName(" in line:
            break
    for i in range(num_params):
        name = lines[index + i].split("\"")[1]
        result["attrs"][i]["name"] = name

    return result

def get_processing_code(num_io):
    lines = []
    with open(airwindows_dir + plugin + "/" + plugin + "Proc.cpp") as f:
        lines = f.readlines()
    
    count = 0
    in_function = False
    start_index = 0
    for line in lines:
        count += 1
        if "processDoubleReplacing(" in line:
            in_function = True
            start_index = count + 2 + num_io

    return lines[start_index:-2].copy()

def get_private_vars():
    lines = []
    result = []

    starting = False

    with open(airwindows_dir + plugin + "/" + plugin + ".h") as f:
        lines = f.readlines()

    for line in lines:
        if starting and "float A" in line:
            break
        if starting:
            result.append(line)
        if "> _canDo;" in line:
            starting = True

    return result

def get_initialization_code(num_io):
    lines = []

    # Get default values from *.cpp constructor
    with open(airwindows_dir + plugin + "/" + plugin + ".cpp") as f:
        lines = f.readlines()
    
    start_index = 0
    end_index = 0
    count = 0
    for line in lines:
        count += 1
        if "AudioEffectX(" in line:
            start_index = count + num_io - 1
        if "_canDo.insert(" in line:
            end_index = count - 1
            break

    return lines[start_index - 2:end_index]

def get_template_help():
    lines = []
    result = []

    with open(pwd + "scripts/template.maxhelp") as f:
        lines = f.readlines()
    
    for line in lines:
        if "ar.TEMPLATE~" in line:
            result.append(line.replace("ar.TEMPLATE~", "ar." + plugin.lower() + "~"))
        elif "PLUGINLINK" in line:
            result.append(line.replace("PLUGINLINK", plugin.lower()))
        else:
            result.append(line)

    return result



def get_object_text(params):
    text = "#include \"c74_min.h\"\n\n"
    text += "using namespace c74::min;\n\n"
    text += "class " + meta["classname"] + " : public object<" + meta["classname"] + ">, public vector_operator<> {\n"
    text += "public:\n"
    text += "\tMIN_DESCRIPTION {\"" + meta["description"] + "\"};\n"
    text += "\tMIN_TAGS {\"audio, effect\"};\n\tMIN_AUTHOR {\"Isabel Kaspriskie\"};\n\n"

    # Create inlets/outlets
    for i in range(params["num_ins"]):
        text += "\tinlet<> in" + str(i + 1) + " {this, \"(signal) Input" + str(i + 1) +"\"};\n"
    for i in range(params["num_outs"]):
        text += "\toutlet<> out" + str(i + 1) + " {this, \"(signal) Output" + str(i + 1) +"\", \"signal\"};\n"

    text += "\n"

    # Create attributes
    for attr in params["attrs"]:
        text += "\tattribute<number, threadsafe::no, limit::clamp> " + attr["variable"] + " {this, \"" + attr["name"] + "\", " + attr["initial_val"] + ", range {0.0, 1.0} };\n"

    text += "\n"

    # Create dspsetup
    text += "\tmessage<> dspsetup {this, \"dspsetup\",\n"
    text += "\t\tMIN_FUNCTION {\n"

    # Add processing code
    init_code = get_initialization_code(params["num_ins"] + params["num_outs"])
    for l in init_code:
        text += "\t\t" + l
    text += "\t\t\treturn {};\n\t\t}\n\t};\n\n"

    # Create operator/processor
    text += "\tvoid operator()(audio_bundle _input, audio_bundle _output) {\n"
    
    #    Create ins and outs
    for i in range(params["num_ins"]):
        text += "\t\tdouble* in" + str(i + 1) + " = _input.samples(" + str(i) + ");\n"
    for i in range(params["num_outs"]):
        text += "\t\tdouble* out" + str(i + 1) + " = _output.samples(" + str(i) + ");\n"

    text += "\t\tdouble overallscale = 1.0;\n\t\toverallscale /= 44100.0;\n\t\toverallscale *= samplerate();\n\n"
    text += "\t\tlong sampleFrames = _input.frame_count();\n\n"

    # Add processing code
    proc_code = get_processing_code(params["num_ins"] + params["num_outs"])
    for l in proc_code:
        text += "\t" + l
    text += "\t\t}\n\t}\n"
    
    #    Add private member variables
    text += "private:\n"
    members = get_private_vars()
    for m in members:
        text += m
    text += "};\n"

    # End
    text += "MIN_EXTERNAL(" + meta["classname"] + ");\n"
    return text


if __name__ == "__main__":
    project_name = "ar." + plugin.lower() + "_tilde"

    # Create a project folder in the projects directory
    try:
        os.mkdir(projects_dir + project_name)
        print("Made dir: " + projects_dir + project_name)
    except FileExistsError:
        print(project_name + "dir already exists")

    # Copy the CMakeLists.txt
    try:
        shutil.copyfile(pwd + "scripts/CMakeLists.txt.in", projects_dir + project_name + "/CMakeLists.txt")
        print("Created CMakeLists.txt")
    except Exception:
        print("Failed to create CMakeLists.txt")
    
    # Copy the template help file
    t = """
        {}
        """.format("".join(get_template_help()))
    with open(pwd + "help/ar." + plugin.lower() + "~.maxhelp", 'w') as f:
        print(t, file=f)

    # Write the cpp
    with open(projects_dir + project_name + "/" + project_name + ".cpp", 'w') as f:
        print(get_object_text(get_param_info()), file=f)

