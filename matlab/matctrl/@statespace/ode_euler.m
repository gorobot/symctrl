function [t, y] = ode_euler(obj, t_span, x0, options)

sz = calllib('matctrl', 'ml_statespace_f_size', obj.cobj_);

opts_ = calllib('matctrl', 'ml_odeoptions_new');
step_sz = calllib('matctrl', 'ml_odeoptions_step_size_get', opts_);

nl = floor((t_span(end) - t_span(1))/step_sz) + 1;

t_result = libpointer('doublePtr', zeros(1, nl));
x_result = libpointer('doublePtr', zeros(1, nl*sz));

calllib('matctrl', ...
        'ml_slv_ode_euler', ...
        obj.cobj_, ...
        t_span, ...
        numel(t_span), ...
        x0, ...
        numel(x0), ...
        t_result, ...
        x_result, ...
        opts_);

t = reshape(t_result.Value, [], 1);
y = reshape(x_result.Value, sz, []).';

clear('t_result');
clear('x_result');

calllib('matctrl', 'ml_odeoptions_free', opts_);
clear('opts_');

end
