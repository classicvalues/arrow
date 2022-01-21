classdef tmexfcn < matlab.unittest.TestCase
    % Tests for mexfcn.

    % Licensed to the Apache Software Foundation (ASF) under one or more
    % contributor license agreements.  See the NOTICE file distributed with
    % this work for additional information regarding copyright ownership.
    % The ASF licenses this file to you under the Apache License, Version
    % 2.0 (the "License"); you may not use this file except in compliance
    % with the License.  You may obtain a copy of the License at
    %
    %   http://www.apache.org/licenses/LICENSE-2.0
    %
    % Unless required by applicable law or agreed to in writing, software
    % distributed under the License is distributed on an "AS IS" BASIS,
    % WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
    % implied.  See the License for the specific language governing
    % permissions and limitations under the License.

    methods(TestClassSetup)
       function addFeatherFunctionsToMATLABPath(testCase)
            import matlab.unittest.fixtures.PathFixture
            % Add Feather test utilities to the MATLAB path.
            testCase.applyFixture(PathFixture('util'));
            % Add featherread and featherwrite to the MATLAB path.
            testCase.applyFixture(PathFixture(fullfile('..', 'src', 'matlab')));
            % Add mexfcn to the MATLAB path.
            testCase.applyFixture(PathFixture(fullfile('..', 'build')));
            % mexfcn must be on the MATLAB path.
            testCase.assertTrue(~isempty(which('mexfcn')), ...
                '''mexfcn'' must be on the MATLAB path. Use ''addpath'' to add folders to the MATLAB path.');
        end
    end

    methods(Test)
        function UnknownMEXFunctionError(testCase)
        % Verifies mexfcn throws an error if an unkown MEX function name 
        % is passed to it.
            errID = "MATLAB:arrow:UnknownMEXFunction";
            fcn = @()mexfcn('NotAFunction');
            testCase.verifyError(fcn, errID);
        end

        function TooFewInputArguementsError(testCase)
        % Verifies mexfcn throws an error if zero input arguments are
        % passed it.
            errID = "MATLAB:arrow:minrhs";
            fcn = @()mexfcn;
            testCase.verifyError(fcn, errID);
        end

        function InvalidFunctionNameDataTypeError(testCase)
        % Verifies mexfcn throws an error if the first input argument is
        % not a character vector.
            errID = "MATLAB:arrow:FunctionNameDataType";
            fcn = @()mexfcn(1);
            testCase.verifyError(fcn, errID);

            fcn = @()mexfcn(categorical);
            testCase.verifyError(fcn, errID);

            fcn = @()mexfcn(datetime(2021, 9, 10));
            testCase.verifyError(fcn, errID);
        end
    end
end
