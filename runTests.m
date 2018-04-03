% This script loads unit tests from the current folder and runs them.
clear
import matlab.unittest.TestSuite
suiteFolder = TestSuite.fromFolder([pwd, '/test']);
result = run(suiteFolder);
