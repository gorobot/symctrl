function loadmatctrl()

if ~libisloaded('matctrl')
    addpath(genpath(fullfile(userpath, 'matctrl')));
    [notfound, warnings] = loadlibrary('matctrl', 'include/matlab_wrapper.hpp');
end

end
