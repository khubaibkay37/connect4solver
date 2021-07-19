import subprocess
def get_cpp_opinion(starting_position,mode = "value"):

    filename = "a.exe"
    proc = subprocess.Popen([f"./{filename}", mode,starting_position],stdout=subprocess.PIPE)
    value = proc.stdout.read().decode('utf-8').strip()
    return (int(value))



def test_file(filename):
    # read file line by line
    with open(filename) as f:
        for line in f:
            starting,link = (line.strip().split(" "))
            link = int(link)
            result = (get_cpp_opinion(starting,"value") == link)
            if not result:
                return False
    return True 
            #print(line.strip().split(",")[1])
            # print(int(line.strip().split(" ")[1]) == get_cpp_opinion(int(line.strip().split(" ")[0])))


print(test_file("Test_L3_R1"))
