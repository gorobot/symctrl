function loadmatctrl()

fprintf('Loading matctrl... ');

if ~libisloaded('matctrl')
    addpath(genpath(fullfile(userpath, 'matctrl')));
    [notfound, warnings] = loadlibrary('matctrl', 'include/matlab_wrapper.hpp');
end

fprintf('done\n');

end
