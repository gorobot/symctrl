function T = subs(obj, old, new)

n = calllib('matctrl', 'ml_statespace_f_size', obj.cobj_);

old_ptr = libpointer('stringPtrPtr', old);
new_ptr = libpointer('stringPtrPtr', new);

calllib('matctrl', ...
        'ml_statespace_subs', ...
        obj.cobj_, ...
        numel(old), ...
        old_ptr, ...
        new_ptr);

% co = old_ptr.Value;
% co = reshape(old_ptr.Value, n, n*m);

clear('old_ptr');
clear('new_ptr');

end
