cimport symengine
from symengine cimport (RCP, map_basic_basic, rcp_const_basic, vec_basic)

cdef extern from "libctrl/state_space.hpp" namespace "Controls":
    cdef cppclass StateSpace:
        StateSpace() except +

        set_states(vec_basic &a)
        vec_basic get_states()
