
from cpp_api import get_value_of_position
def test_file(filename):
    """
    Reads the file which contains testcases in each line
    of the format <position> <score of position> and calls
    the C++ api to see if the api gets the score correctly.
    It returns whether the API is working properly or not.

    Args:
        filename [string]: link to the file containing testcases

    Returns:
        [Boolean]: Whether all testcases pass or not
    """
    with open(filename) as test_case_file:
        testcases = test_case_file.readlines()
        
    for testcase in testcases:
        position , position_score = (testcase.strip().split(" "))
        position_score = int(position_score)
        result = get_value_of_position(position,"value") == position_score
        if not result:
            return False
    return True 

if __name__ == "main":
    testcase_filename = "Test_L3_R1"
    print(test_file(testcase_filename))
