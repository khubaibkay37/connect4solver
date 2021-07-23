import time
from cpp_api import get_score_of_position
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
        
    for i,testcase in enumerate(testcases):
        position , position_score = (testcase.strip().split(" "))
        position_score = int(position_score)
        result = get_score_of_position(position) == position_score
        if not result:
            return False
        print("Testcase {} passed".format(i))
        # print(result)
    return True 

if __name__ == "__main__":
    testcase_filename = "Test_L3_R1"
    # see how much time the function takes
    start_time = time.time()
    result = test_file(testcase_filename)
    end_time = time.time()
    print("Time taken: {}".format(end_time - start_time))
    if result:
        print("All testcases passed")
