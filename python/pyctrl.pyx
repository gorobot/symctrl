# # distutils: libraries = symengine
# # distutils: library_dirs = /usr/local/lib, /usr/local/lib/python3.6/site-packages/symengine/lib
# # distutils: include_dirs = /usr/local/include, /usr/local/lib/python3.6/site-packages/symengine/lib
#
# from cython.operator cimport dereference as deref, preincrement as inc
# from libcpp.vector cimport vector
#
# cimport symengine
# from symengine cimport (RCP, map_basic_basic, rcp_const_basic, vec_basic)
#
# cimport symengine_wrapper
# from symengine_wrapper cimport c2py
#
# cimport symengine
# from symengine cimport (RCP, map_basic_basic, rcp_const_basic, vec_basic)
#
# # Python wrapper functions.
#
# cimport pyctrl
#
# # cdef extern from "libctrl/state_space.hpp" namespace "Controls":
# #     cdef cppclass StateSpace:
# #         StateSpace() except +
# #
# #         set_states(vec_basic &a)
# #         vec_basic get_states()
# 
# # Helper functions.
# cdef tuple vec_basic_to_tuple(vec_basic& vec):
#     return tuple(vec_basic_to_list(vec))
#
# cdef list vec_basic_to_list(vec_basic& vec):
#     result = []
#     for i in range(vec.size()):
#         result.append(c2py(<rcp_const_basic>(vec[i])))
#     return result
#
# # Class definitions.
# cdef class symss(object):
#     cdef StateSpace* thisptr
#
#     def __cinit__(self):
#         self.thisptr = new StateSpace()
#
#     def __dealloc__(self):
#         del self.thisptr
#
#     property states:
#         def __get__(self):
#             cdef vec_basic states = self.thisptr.get_states()
#             return vec_basic_to_tuple(states)
#
#             # def __set__(self, a):
#             #     self.thisptr.set_states(a)

# class symss:
def say_hello():
    print("Hello")
